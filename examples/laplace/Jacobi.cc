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

using namespace acm114::laplace;

// interface
void Jacobi::solve(Problem & problem) {
    Grid & current = problem.solution();

    // create and initialize temporary storage
    Grid next(current.size());
    problem.initialize(next);

    // let's get going
    std::cout << "jacobi: tolerance=" << _tolerance << std::endl;

    // put an upper bound on the number of iterations
    size_t max_iterations = (size_t) 1.0e4;
    for (size_t iterations = 0; iterations<max_iterations; iterations++) {
        if (iterations % 100 == 0) {
            std::cout << "     " << iterations << std::endl;
        }
        double max_dev = 0.0;
        // do an iteration step
        // leave the boundary alone
        // iterate over the interior of the grid
        for (size_t j=1; j < current.size()-1; j++) {
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
        // swap the blocks between the two grids
        Grid::swapBlocks(current, next);
        // check covergence
        if (max_dev < _tolerance) {
            std::cout << " ### convergence in " << iterations << " iterations!" << std::endl;
            break;
        }
    }
    std::cout << " --- done." << std::endl;

    // compute and store the error
    std::cout << "  computing absolute error" << std::endl;

    //  compute the relative error
    const Grid & exact = problem.exact();
    Grid & error = problem.error();
    for (size_t j=0; j < exact.size(); j++) {
        for (size_t i=0; i < exact.size(); i++) {
            if (exact(i,j) == 0.0) {
                error(i,j) = std::abs(current(i,j));
            } else {
                error(i,j) = std::abs(current(i,j) - exact(i,j))/exact(i,j);
            }
        }
    }
    std::cout << " --- done." << std::endl;

    return;
}

// destructor
Jacobi::~Jacobi() {}

// end of file
