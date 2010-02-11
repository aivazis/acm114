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
#include <cstdlib>

#include "Example.h"
#include "Grid.h"

using namespace acm114::laplace;

const double pi = M_PI;

// destructor
Example::~Example() {}

// grid initialization
void Example::initialize(Grid & g) {
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
