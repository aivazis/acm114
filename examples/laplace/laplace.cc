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

#include <getopt.h>
#include <cstdlib>
#include <iostream>

#include "Example.h"
#include "Jacobi.h"
#include "Visualizer.h"

using namespace acm114::laplace;

// main program
int main(int argc, char* argv[]) {
    // default values for our user configurable settings
    size_t N = 9;
    size_t threads = 1;
    double tolerance = 1.0e-3;

    // read the command line
    int command;
    while ((command = getopt(argc, argv, "N:e:p:t:")) != -1) {
        switch (command) {
        // get the convergence tolerance
        case 'e':
            tolerance = atof(optarg);
            break;
        // get the grid size
        case 'N':
            N = (size_t) atof(optarg);
            break;
        // get the number of threads
        case 't':
            threads = (size_t) atoi(optarg);
            break;
        }
    }
    // print out the chosen options
    for (int arg = 0; arg < argc; ++arg) {
        std::cout << argv[arg] << " ";
    }
    std::cout << std::endl
        << "    grid size: " << N << std::endl
        << "      workers: " << threads << std::endl
        << "    tolerance: " << tolerance << std::endl;

    // instantiate a problem
    Example problem("cliche", 1.0, N);
    //  instantiate a solver
    Jacobi solver(tolerance, threads);
    // solve
    solver.solve(problem);
    // save the results
    Visualizer vis;
    vis.csv(problem);
    // all done
    return 0;
}

// end of file
