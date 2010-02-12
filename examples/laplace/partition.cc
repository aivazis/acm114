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
#include <iomanip>

// main program
int main(int argc, char* argv[]) {
    // default values for our user configurable settings
    size_t N = 9;
    size_t threads = 1;

    // read the command line
    int command;
    while ((command = getopt(argc, argv, "N:t:")) != -1) {
        switch (command) {
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
    std::cout
        << std::endl
        << "    grid size: " << N << std::endl
        << "      workers: " << threads << std::endl;

    for (size_t id = 0; id < threads; ++id) {
        std::cout << "          " << std::setw(3) << id << ": ";
        for (size_t row = id; row < N; row+=threads) {
            std::cout << row << " ";
        }
        std::cout << std::endl;
    }

    // all done
    return 0;
}

// end of file
