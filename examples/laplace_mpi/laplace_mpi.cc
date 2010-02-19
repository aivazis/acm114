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
#include <cmath>

#include "mpi.h"

#include "Example.h"
#include "Jacobi.h"
#include "Visualizer.h"

using namespace acm114::laplace;

// main program
int main(int argc, char* argv[]) {
    int status;
    // initialize mpi
    status = MPI_Init(&argc, &argv);
    if (status) {
        throw("error in MPI_Init");
    }
    // get my rank in the world communicator
    int worldRank, worldSize;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    size_t processors = static_cast<size_t>(std::sqrt(worldSize));

    // default values for our user configurable settings
    size_t n = 9; // points per processor
    size_t threads = 1;
    double tolerance = 1.0e-3;

    // read the command line
    int command;
    while ((command = getopt(argc, argv, "n:e:t:")) != -1) {
        switch (command) {
        // get the convergence tolerance
        case 'e':
            tolerance = atof(optarg);
            break;
        // get the grid size
        case 'n':
            n = (size_t) atof(optarg);
            break;
        // get the number of threads
        case 't':
            threads = (size_t) atoi(optarg);
            break;
        }
    }
    // print out the chosen options
    if (worldRank == 0) {
        for (int arg = 0; arg < argc; ++arg) {
            std::cout << argv[arg] << " ";
        }
        std::cout
            << std::endl
            << "    grid size: " << n << std::endl
            << "      workers: " << threads << std::endl
            << "    tolerance: " << tolerance << std::endl;
    }

    // instantiate a problem
    Example problem("cliche", 1.0, processors, n);

    // instantiate a solver
    Jacobi solver(tolerance, threads);
    // solve
    solver.solve(problem);
    // save the results
    Visualizer vis;
    vis.csv(problem);

    // initialize mpi
    status = MPI_Finalize();
    if (status) {
        throw("error in MPI_Finalize");
    }

    // all done
    return 0;
}

// end of file
