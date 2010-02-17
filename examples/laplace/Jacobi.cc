// -*- C++ -*-
// -*- coding: utf-8 -*-
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//                             michael a.g. aïvázis
//                      california institute of technology
//                      (c) 1998-2010  all rights reserved
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <portinfo>

#include "Jacobi.h"
#include "Grid.h"
#include "Problem.h"

#include <iostream>
#include <cmath>
#include <pthread.h>

using namespace acm114::laplace;

struct Task {
    // shared information 
    size_t workers;
    double tolerance; // the covergence tolerance
    Grid & current;
    Grid & next;

    bool done; // is there more work?
    double maxDeviation; // the value
    size_t contributions; // the number of threads that have deposited contributions
    pthread_mutex_t errorUpdate_lock; //the mutex
    pthread_mutex_t gridUpdate_lock; //the mutex
    pthread_cond_t gridUpdate_check;

    Task(size_t workers, double tolerance, Grid & current, Grid & next) :
        workers(workers), tolerance(tolerance), current(current), next(next),
        done(false), maxDeviation(0.0), contributions(0),
        gridUpdate_lock(), gridUpdate_check() {
        // initialize the convergence criterion lock
        pthread_mutex_init(&errorUpdate_lock, 0);
        pthread_mutex_init(&gridUpdate_lock, 0);
        pthread_cond_init(&gridUpdate_check, 0);
    }

    ~Task() {
        pthread_mutex_destroy(&errorUpdate_lock);
        pthread_mutex_destroy(&gridUpdate_lock);
        pthread_cond_destroy(&gridUpdate_check);
    }
};

struct Context {
    // thread info
    size_t id;
    pthread_t descriptor;
    Task * task;
};

// interface
void Jacobi::solve(Problem & problem) {
    // initialize the problem
    problem.initialize();
    // do the actual solve
    _solve(problem);
    // compute and store the error
    std::cout << "  computing absolute error" << std::endl;
    //  compute the relative error
    Grid & error = problem.error();
    const Grid & exact = problem.exact();
    const Grid & solution = problem.solution();

    for (size_t j=0; j < exact.size(); j++) {
        for (size_t i=0; i < exact.size(); i++) {
            if (exact(i,j) == 0.0) {
                error(i,j) = std::abs(solution(i,j));
            } else {
                error(i,j) = std::abs(solution(i,j) - exact(i,j))/exact(i,j);
            }
        }
    }
    std::cout << " --- done." << std::endl;
    return;
}

// the solve worker
void Jacobi::_solve(Problem & problem) {
    Grid & current = problem.solution();

    // create and initialize temporary storage
    Grid next(current.size());
    problem.initialize(next);

    // shared thread info
    Task task(_workers, _tolerance, current, next);
    // per-thread information
    Context context[_workers];
    // let's get going
    std::cout << "jacobi: tolerance=" << _tolerance << std::endl;
    // spawn the threads
    std::cout << "jacobi: spawning " << _workers << " threads" << std::endl;
    for (size_t tid=0; tid < _workers; tid++) {
        context[tid].id = tid;
        context[tid].task = &task;
        
        int status = pthread_create(&context[tid].descriptor, 0, _update, &context[tid]);
        if (status) {
            throw ("error in pthread_create");
        }
    }
    // harvest the threads
    std::cout << "jacobi: harvesting " << _workers << " threads" << std::endl;
    for (size_t tid = 0; tid < _workers; tid++) {
            std::cout << "jacobi: waiting for thread " << tid << " to finish" << std::endl;
            pthread_join(context[tid].descriptor, 0);
            std::cout << "jacobi: thread " << tid << " done" << std::endl;
        }
    // done
    std::cout << "jacobi: done." << std::endl;
    return;
}

// the threaded update
void * Jacobi::_update(void * arg) {
    Context * context = static_cast<Context *>(arg);

    size_t id = context->id;
    Task * task = context->task;

    const size_t workers = task->workers;
    Grid & current = task->current;
    Grid & next = task->next;

    std::cout << "thread " << id << ": hello!" << std::endl;

    size_t maxIterations = (size_t) 1e4;
    // iterate, updating the grid until done
    for (size_t iterations = 0; iterations < maxIterations; iterations++) {
        //
        std::cout << "thread " << id << ": updating the grid: iteration " << iterations << std::endl;
        // thread 0: print an update
        if (id == 0 && iterations % 100 == 0) {
            std::cout << "     " << iterations << std::endl;
        }

        double max_dev = 0.0;
        // do an iteration step
        // leave the boundary alone
        // iterate over the interior of the grid
        for (size_t j=id+1; j < current.size()-1; j+=workers) {
            for (size_t i=1; i < current.size()-1; i++) {
                next(i,j) = 0.25*(current(i+1,j)+current(i-1,j)+current(i,j+1)+current(i,j-1));
                // compute the deviation from the last generation
                double dev = std::abs(next(i,j) - current(i,j));
                // and update the maximum deviation
                if (dev > max_dev) {
                    max_dev = dev;
                }
            }
        }
        std::cout << "thread " << id << ": done updating the grid" << std::endl;
        // done with the grid update
        // grab the grid update lock
        pthread_mutex_lock(&task->errorUpdate_lock);
        std::cout << "thread " << id << ": tolerance: " << task->tolerance << std::endl;
        std::cout << "thread " << id << ": maximum deviation: " << max_dev << std::endl;
        std::cout << "thread " << id << ": global deviation: " << task->maxDeviation << std::endl;
        // update the global maximum deviation 
        if (task->maxDeviation < max_dev) {
            task->maxDeviation = max_dev;
        }
        // leave a mark
        task->contributions++;
        pthread_mutex_unlock(&task->errorUpdate_lock);

        // synchronize
        pthread_mutex_lock(&task->gridUpdate_lock);
        if (task->contributions == workers) {
            // if i am the slowest worker
            std::cout << "thread " << id << ": last to finish!" << std::endl;
            // swap the blocks between the two grids
            Grid::swapBlocks(current, next);
            // check covergence
            std::cout << "thread " << id << ": checking convergence" << std::endl;
            if (task->maxDeviation < task->tolerance) {
                std::cout << " ### convergence in " << iterations << " iterations!" << std::endl;
                task->done = true;
            }
            // signal everybody else
            std::cout << "thread " << id << ": signaling the others" << std::endl;
            // reset the update count
            task->contributions = 0;
            task->maxDeviation = 0;
            pthread_cond_broadcast(&task->gridUpdate_check);
        } else {
            // all but the slowest wait here
            std::cout << "thread " << id << ": waiting for signal" << std::endl;
            pthread_cond_wait(&task->gridUpdate_check, &task->gridUpdate_lock);
            std::cout << "thread " << id << ": signal received" << std::endl;
        } 
        // release
        std::cout << "thread " << id << ": releasing the grid update lock" << std::endl;
        pthread_mutex_unlock(&task->gridUpdate_lock);

        // check whether we are done
        if (task->done) {
            std::cout << "thread " << id << ": all done" << std::endl;
            break;
        }
    }
    
    return 0;
}


// destructor
Jacobi::~Jacobi() {}

// end of file
