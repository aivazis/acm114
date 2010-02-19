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

// interface
void Jacobi::solve(Problem & problem) {
    // initialize the problem
    problem.initialize();

    // get a reference to the solution grid
    Grid & current = problem.solution();
    // build temporary storage for the next iterant
    Grid next(current.size());

    // put an upper limit on the number of iterations
    size_t maxIterations = (size_t) 1e4;
    for (size_t iteration = 0; iteration < maxIterations; iteration++) {
        // print out a progress repot
        if ((problem.rank() == 0) && (iteration % 100 == 0)) {
            std::cout 
                << "jacobi: iteration " << iteration
                << std::endl;
        }
        // enforce  the boundary conditions
        problem.applyBoundaryConditions();
        // reset the local maximum change
        double localMax = 0.0;
        // update the interior of the grid
        for (size_t j=1; j < next.size()-1; j++) {
            for (size_t i=1; i < next.size()-1; i++) {
                // the cell update
                next(i,j) = .25*(current(i+1,j)+current(i-1,j)+current(i,j+1)+current(i,j-1));
                // compute the change from the current cell value
                double dev = std::abs(next(i,j) - current(i,j));
                // and update the local maximum
                if (dev > localMax) {
                    localMax = dev;
                }
            }
        } // done with the grid update
        // swap the blocks of the two grids, leaving the solution in current
        Grid::swapBlocks(current, next);
        // compute global maximum deviation
        double globalMax;
        MPI_Allreduce(&localMax, &globalMax, 1, MPI_DOUBLE, MPI_MAX, problem.communicator());
        // convergence check
        if (globalMax < _tolerance) {
            if (problem.rank() == 0) {
                std::cout 
                    << "jacobi: convergence in " << iteration << " iterations"
                    << std::endl;
            }
            break;
        }
        // otherwise
    }
    // when we get here, either we have converged or ran out of iterations
    // update the fringe of the current grid
    problem.applyBoundaryConditions();
    // all  done
    return;
}

// destructor
Jacobi::~Jacobi() {}

// end of file
