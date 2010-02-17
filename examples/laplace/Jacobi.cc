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
    Grid & current;
    Grid & next;
    // convergence criterion management
    double maxDeviation; // the value
    size_t contributions; // the number of threads that have deposited contributions
    pthread_mutex_t updateDeviation; //the mutex
    // job management
    bool done;
    pthread_cond_t gridUpdated;
    pthread_mutex_t gridUpdateLock;

    Task(size_t workers, Grid & current, Grid & next) :
        workers(workers), current(current), next(next),
        maxDeviation(0.0), contributions(0), updateDeviation(),
        done(false), gridUpdated(), gridUpdateLock() {
        // initialize the convergence criterion lock
        pthread_mutex_init(&updateDeviation, 0);
        pthread_cond_init(&gridUpdated, 0);
        pthread_mutex_init(&gridUpdateLock, 0);
    }

    ~Task() {
        pthread_mutex_destroy(&updateDeviation);
        pthread_cond_destroy(&gridUpdated);
        pthread_mutex_destroy(&gridUpdateLock);
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
    Task task(_workers, current, next);
    // per-thread information
    Context context[_workers];

    // let's get going
    std::cout << "jacobi: tolerance=" << _tolerance << std::endl;

    // put an upper bound on the number of iterations
    const size_t max_iterations = (size_t) 1.0e4;
    for (size_t iterations = 0; iterations<max_iterations; iterations++) {
        if (iterations % 1 == 0) {
            std::cout << "     " << iterations << std::endl;
        }

        // reset the maximium deviation and associated counter
        task.contributions = 0;
        task.maxDeviation = 0.0;

        // spawn the threads
        for (size_t tid=0; tid < _workers; tid++) {
            context[tid].id = tid;
            context[tid].task = &task;

            int status = pthread_create(&context[tid].descriptor, 0, _update, &context[tid]);
            if (status) {
                throw ("error in pthread_create");
            }
        }
        // wait until the update is done
        pthread_mutex_lock(&task.gridUpdateLock);
        pthread_cond_wait(&task.gridUpdated, &task.gridUpdateLock);
        std::cout << "main thread: grid has been updated" << std::endl;
        pthread_mutex_unlock(&task.gridUpdateLock);

        // harvest the threads
        for (size_t tid = 0; tid < _workers; tid++) {
            std::cout << "waiting for thread " << tid << " to finish" << std::endl;
            pthread_join(context[tid].descriptor, 0);
            std::cout << "thread " << tid << " done" << std::endl;
        }

        // swap the blocks between the two grids
        Grid::swapBlocks(current, next);
        // check covergence
        if (task.maxDeviation < _tolerance) {
            std::cout << " ### convergence in " << iterations << " iterations!" << std::endl;
            break;
        }
    }
    std::cout << " --- done." << std::endl;

    return;
}

// the threaded update
void * Jacobi::_update(void * arg) {
    Context * context = static_cast<Context *>(arg);

    size_t id = context->id;
    Task * task = context->task;

    size_t workers = task->workers;
    Grid & current = task->current;
    Grid & next = task->next;
    pthread_mutex_t updateDeviation = task->updateDeviation;

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

    // grab the lock and update the global maximum deviation
    pthread_mutex_lock(&updateDeviation);
    if (task->maxDeviation < max_dev) {
        task->maxDeviation = max_dev;
    }
    task->contributions++;
    if (task->contributions == task->workers) {
        pthread_mutex_lock(&task->gridUpdateLock);
        std::cout << "thread " << id << ": last to finish!" << std::endl;
        pthread_cond_signal(&task->gridUpdated);
        pthread_mutex_unlock(&task->gridUpdateLock);
    }
    pthread_mutex_unlock(&updateDeviation);

    return 0;
}


// destructor
Jacobi::~Jacobi() {}

// end of file
