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

#include <getopt.h> // for getopt and friends
#include <cuda.h>

#include <cmath>
#include <iostream>


// each thread computes 
__global__ void dilog_cuda(float* array, float zp, long workers, long subdivisions) {
    // compute its offset using the block geometry builtins
    int idx = blockIdx.x * blockDim.x  + threadIdx.x;
    // make sure we don't go past the last one
    if (idx < workers && idx < subdivisions) {
        float sum = 0.0f;
        long load = subdivisions/workers;

        float dz = zp/subdivisions;
        float z = (idx-1.f)*load*dz + dz/2;

        for (int i=0; i<load; i++) {
            sum += log(1-z)/z;
            z += dz;
        }
        // do the arithmetic
        array[idx] = sum;
    }
    return;
}

int main(int argc, char* argv[]) {
    //  default values for the command line options
    long N = 1000;
    double z = 1.0;
    // read the command line
    int command;
    while ((command = getopt(argc, argv, "z:N:")) != -1) {
        switch (command) {
        case 'z':
            // get the argument of the dilogarithm 
            z = atof(optarg);
            break;
        case 'N':
            // get the number of subdivisions
            N = (long) atof(optarg);
            break;
        }
    }

    // geometry
    int warp = 32;
    int cores = 8;
    int processors = 30;
    size_t workers = processors*cores*warp;
    // allocate a block on the host
    float* partials_host = new float[workers];
    for (int i=0; i<workers; i++) {
        partials_host[i] = 0.f;
    }
    // allocate a block on the device
    float* partials_dev;
    cudaMalloc((void **) &partials_dev, workers*sizeof(float));
    // send the data from the host to the device
    cudaMemcpy(partials_dev, partials_host, workers*sizeof(float), cudaMemcpyHostToDevice);

    // set up the device execution context for our threads
    // each thread will take care of one element
    int blockSz = warp; // a warp at a time
    // compute the number of blocks needed
    int nBlocks = cores*processors;
    // compute the load per thread
    long load = N/workers + 1;
    N = load*workers;
    float dz = z/N;
    // compute
    dilog_cuda <<<nBlocks, blockSz>>> (partials_dev, z, (long)workers, N);
    // get the partials back on the host
    cudaMemcpy(partials_host, partials_dev, workers*sizeof(float), cudaMemcpyDeviceToHost);

    // do the reduction
    double sum = 0.f;
    for (int i=0; i<workers; i++) {
        sum += partials_host[i];
    }
    sum *= -dz;

    std::cout << "sum = " << sum << std::endl;
    // all done
    return 0;
}

// end of file
