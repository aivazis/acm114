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
#include <cmath>

#include "Example.h"

using namespace acm114::laplace;

const double pi = M_PI;

// destructor
Example::~Example() {}

// grid initialization
void Example::initialize() {
    // initialize the solution grid
    initialize(_solution);

    // initialize the error grid
    _error.clear(1.0);

    // initialize the representation of the exact solution
    // paint the exact solution
    // and ompute how far the exact solution is from satisfying the update rule
    for (size_t j=0; j < _exact.size(); j++) {
        for (size_t i=0; i < _exact.size(); i++) {
            double x = i*_delta;
            double y = j*_delta;
            _exact(i,j) = std::exp(-pi*y)*std::sin(pi*x);
        }
    }

    // initialize the deviation map
    _deviation.clear(0);
    for (size_t j=1; j < _exact.size()-1; j++) {
        for (size_t i=1; i < _exact.size()-1; i++) {
            double avrg = 0.25*(_exact(i+1,j)+_exact(i-1,j)+_exact(i,j+1)+_exact(i,j-1));
            _deviation(i,j) = std::abs(avrg-_exact(i,j))/_exact(i,j);
        }
    }

    return;
}

// implementation detail
void Example::initialize(Grid & g) const {
    // initialize the solution grid
    // clear out the grid memory
    g.clear(1.0);
    // apply the dirichlet conditions
    for (size_t cell=0; cell < g.size(); cell++) {
        // evaluate sin(pi x)
        double sin = std::sin(cell*_delta*pi);
        // along the x-axis, at top and bottom
        g(cell, 0) = sin;
        g(cell, g.size()-1) = sin * std::exp(-pi);
        // along the y-axis, left and right
        g(0, cell) = g(g.size()-1, cell) = 0.0;
    }

    return;
}


// end of file
