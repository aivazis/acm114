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

int main(int argc, char* argv[]) {
    const int N = 12;
    // allocate some buffers on the host
    float *send_host = (float *) malloc(N*sizeof(float));
    float *recv_host = (float *) malloc(N*sizeof(float));
    // allocate matching ones on the device
    float *send_device, *recv_device;
    cudaMalloc((void **) &recv_device, N*sizeof(float));
    cudaMalloc((void **) &send_device, N*sizeof(float));
    // and initialize the host data
    for (int i=0; i<N; i++) {
        send_host[i] = 2.0f + i*i;
        recv_host[i] = 0.0f;
    }
    // send the data from the host to the device
    cudaMemcpy(recv_device, send_host, N*sizeof(float), cudaMemcpyHostToDevice);
    // move the data in device memory
    cudaMemcpy(send_device, recv_device, N*sizeof(float), cudaMemcpyDeviceToDevice);
    // get it back on the host
    cudaMemcpy(recv_host, send_device, N*sizeof(float), cudaMemcpyDeviceToHost);
    // check the result
    for (int i=0; i<N; i++) {
      assert(send_host[i] == recv_host[i]);
    }
    // free the buffers;
    free(send_host); free(recv_host);
    cudaFree(send_device); cudaFree(recv_device);

    return 0;
}

// end of file
