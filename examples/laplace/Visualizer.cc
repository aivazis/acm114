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

    // build file stream for our three grids
    std::ofstream exact((seed+"-exact.csv").c_str());
    std::ofstream error((seed+"-error.csv").c_str());
    std::ofstream solution((seed+"-solution.csv").c_str());
    std::ofstream deviation((seed+"-deviation.csv").c_str());

    // build a visualizer and let it render
    Visualizer v;
    renderCSV(problem.exact(), exact);
    renderCSV(problem.error(), error);
    renderCSV(problem.solution(), solution);
    renderCSV(problem.deviation(), deviation);

    return;

}

// end of file
