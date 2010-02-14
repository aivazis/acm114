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
#include <cstdlib>
#include <cmath>
#include <iostream>

#include <getopt.h>
#include <assert.h>
#include "timers.h"

// main program
int main(int argc, char* argv[]) {
    pyre::timer_t total("total");
    total.start();
    // default values for our user configurable settings
    const size_t kb = 1024;
    const size_t Mb = 1024*kb;
    const size_t Gb = 1024*Mb;
    
    const double pi = M_PI;

    size_t N = 1;
    size_t threads = 1;

    // read the command line
    int command;
    while ((command = getopt(argc, argv, "N:s:t:")) != -1) {
        switch (command) {
        // get the sample size in Gb
        case 'N':
            N = (size_t) atof(optarg);
            break;
        // get the number of threads
        case 't':
            threads = (size_t) atoi(optarg);
            break;
        }
    }
    // build an array of strides to check
    size_t strides[9*9];
    for (int exp=0; exp < 9; exp++) {
        for (int factor=1; factor < 10; factor++) {
            strides[exp*9+factor-1] = factor*pow(10,exp);
        }
    }

    // compute how many doubles fit in our buffer
    size_t doubles = N*Gb/sizeof(double);

    // print out the chosen options
    std::cout << argv[0] << ":" << std::endl;
    std::cout << "         args: ";
    for (int arg = 1; arg < argc; ++arg) {
        std::cout << argv[arg] << " ";
    }
    std::cout << std::endl;

    std::cout 
        << "  buffer size: " << N << " Gb, or " << doubles << " doubles" << std::endl
        << "      workers: " << threads << std::endl;

    // allocate the source buffer
    double * src = new double[doubles];
    // allocate the destination buffer
    double * dst = new double[doubles];

    // initialize the source
    pyre::timer_t init("init");
    init.start();
    for (size_t idx=0; idx < doubles; ++idx) {
        src[idx] = pi;
    }
    init.stop();

    // copy
    pyre::timer_t copy("copy");
    for (size_t pass=0; pass<sizeof(strides)/sizeof(strides[0]); pass++) {
        copy.reset();
        copy.start();
        size_t stride = strides[pass];
        for (size_t start=0; start < stride; start++) {
            for (size_t idx=start; idx < doubles; idx+=stride) {
                dst[idx] = src[idx];
                // std::cout << " " << idx;
            }
            // std::cout << std::endl;
        }
        copy.stop();
        std::cout << stride << "," << copy.read() << std::endl;
        // chekc the copy took place
        for (size_t idx=0; idx < doubles; ++idx) {
            assert(src[idx] == dst[idx]);
        }
    }

    // shut down the application timer
    total.stop();
    // delete the buffers
    delete [] src;
    delete [] dst;
    // all done
    return 0;
}

// end of file
