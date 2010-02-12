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
    double maxDeviation;
    pthread_mutex_t lock; // mutex to control access to the convergence criterion

    Task(size_t workers, Grid & current, Grid & next) :
        workers(workers), current(current), next(next), maxDeviation(0.0) {
        pthread_mutex_init(&lock, 0);
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
        if (iterations % 100 == 0) {
            std::cout << "     " << iterations << std::endl;
        }

        // reset the maximium deviation
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
        // harvest the threads
        for (size_t tid = 0; tid < _workers; tid++) {
            pthread_join(context[tid].descriptor, 0);
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
    pthread_mutex_t lock = task->lock;

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
    pthread_mutex_lock(&lock);
    if (task->maxDeviation < max_dev) {
        task->maxDeviation = max_dev;
    }
    pthread_mutex_unlock(&lock);

    return 0;
}


// destructor
Jacobi::~Jacobi() {}

// end of file
