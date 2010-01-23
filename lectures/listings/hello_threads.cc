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

#include <pthread.h>
#include <iostream>
#define THREADS 10

// worker
void* hello(void* threadID) {
    long id = (long) threadID;
    std::cout << "hello from " << id << "!" << std::endl;
    pthread_exit(0);
    return 0;
}

// main program
int main(int argc, char* argv[]) {
    pthread_t threads[THREADS];
    
    // spawn some threads
    for (long id=0; id<THREADS; id++) {
        std::cout << "creating thread " << id << std::endl;
        int status = pthread_create(&threads[id], 0, hello, (void*) id);
        if (status) {
            std::cout << "error " << status << " in pthread_create" << std::endl;
        }
    }

    // harvest the threads
    for (long id=0; id<THREADS; id++) {
        pthread_join(threads[id], 0);
    }

    // all done
    pthread_exit(0);
    return 0;
}

// end of file
