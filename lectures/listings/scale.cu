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

// memxchng.cu
#include <cuda.h>
#include <assert.h>


// manipulate the host array
void scale_host(float* array, float scale, int N) {
    // loop over all array elements and multiply them by 2 
    for (int idx=0; idx<N; idx++) {
        array[idx] *= scale;
    }
    return;
}

// and here is the corresponding code for the GPU
__global__ void scale_dev(float* array, float scale, int N) {
    // this thread is responsible for one element of the array
    // compute its offset using the block geometry builtins
    int idx = blockIdx.x * blockDim.x  + threadIdx.x;
    // make sure we don't do go past the last one
    if (idx < N) {
        // do the arithmetic
        array[idx] *= scale;
    }
    return;
}

int main(int argc, char* argv[]) {
    const int N = 12;
    // allocate some buffers on the host
    float* send_host = (float *) malloc(N*sizeof(float));
    float* recv_host = (float *) malloc(N*sizeof(float));
    // allocate matching ones on the device
    float* array_dev;
    cudaMalloc((void **) &array_dev, N*sizeof(float));

    // and initialize the host data
    for (int i=0; i<N; i++) {
        send_host[i] = 2.0f + i*i;
        recv_host[i] = 0.0f;
    }

    // send the data from the host to the device
    cudaMemcpy(array_dev, send_host, N*sizeof(float), cudaMemcpyHostToDevice);

    // set up the device execution context for our threads
    // each thread will take care of one element
    int blockSz = 4; // 4 threads per block
    // compute the number of blocks needed
    int nBlocks = N/blockSz; 
    // adjust up to make sure we cover the entire array
    if (N % nBlocks) {
        nBlocks++;
    }
    // scale the array on the device
    float scale = 2.0f;
    scale_dev <<<nBlocks, blockSz>>> (array_dev, scale, N);
    // scale the input array on the host
    scale_host(send_host, scale, N);

    // get it back on the host
    cudaMemcpy(recv_host, array_dev, N*sizeof(float), cudaMemcpyDeviceToHost);

    // check the result
    for (int i=0; i<N; i++) {
      assert(send_host[i] == recv_host[i]);
    }
    // free the buffers;
    cudaFree(array_dev);
    free(send_host); free(recv_host);

    return 0;
}

// end of file
