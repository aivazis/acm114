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
#include <fstream>

#include "Problem.h"
#include "Visualizer.h"

using namespace acm114::laplace;

// persist the results
void Problem::csv(string_t seed) const {
    // build file stream for our three grids
    std::ofstream exact((seed+"-exact.csv").c_str());
    std::ofstream error((seed+"-error.csv").c_str());
    std::ofstream solution((seed+"-solution.csv").c_str());
    std::ofstream deviation((seed+"-deviation.csv").c_str());

    // build a visualizer and let it render
    Visualizer v;
    v.csv(_exact, exact);
    v.csv(_error, error);
    v.csv(_solution, solution);
    v.csv(_deviation, deviation);

    return;
}

// destructor
Problem::~Problem() {}

// end of file
