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

#include "Visualizer.h"
#include "Problem.h"

#include <fstream>

using namespace acm114::laplace;

static void renderCSV(const Grid & grid, Visualizer::stream_t & stream) {
    for (size_t j=0; j < grid.size(); j++) {
        stream << j;
        for (size_t i=0; i < grid.size(); i++) {
            stream << "," << grid(i,j);
        }
        stream << std::endl;
    }

    return;
}

// the Visualizer class implementation
void Visualizer::csv(const Problem & problem) {
    Problem::string_t seed = problem.name();

    // build a visualizer
    Visualizer v;
    // build file stream for our three grids
    std::ofstream solution((seed+"-solution.csv").c_str());
    // and render
    renderCSV(problem.solution(), solution);

    return;

}

// end of file
