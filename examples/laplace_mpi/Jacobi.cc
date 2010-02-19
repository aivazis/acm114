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
    // do the actual solve
    _solve(problem);
    // all done
    return;
}

// the solve worker
void Jacobi::_solve(Problem & problem) {
    return;
}


// destructor
Jacobi::~Jacobi() {}

// end of file
