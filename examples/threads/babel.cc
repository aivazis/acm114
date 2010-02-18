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

#include "Guard.h"

using namespace pyre::threads;

// thread management
struct Context {
    // thread info
    size_t id;
    size_t workers;
    size_t iterations;
    Guard<std::ostream> * guard;
    pthread_t descriptor;
};

void * _boast(void * dummy) {
    Context * info = static_cast<Context *>(dummy);

    // iterate
    for (size_t iteration = 0; iteration < info->iterations; iteration++) {
        std::cout
            << *(info->guard)
            << "thread " << info->id << ": iteration " << iteration
            << std::endl
            << *(info->guard)
            ;
    }

    return 0;
}

// main program
int main(int argc, char* argv[]) {
    // default values for our user configurable settings
    size_t threads = 1;
    size_t iterations = 10;

    // read the command line
    int command;
    while ((command = getopt(argc, argv, "n:t:")) != -1) {
        switch (command) {
        // get the number of iterations
        case 'n':
            iterations = (size_t) atof(optarg);
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
    // and our understanding
    std::cout << std::endl
        << "      workers: " << threads << std::endl
        << "   iterations: " << iterations << std::endl;

    // set up the thread context
    Context context[threads];

    // set up a mutex
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, 0);

    // build the iostream lock
    Guard<std::ostream> guard(mutex);

    // spawn some threads
    for (size_t id = 0; id < threads; id++) {
        context[id].id = id;
        context[id].workers = threads;
        context[id].iterations = iterations;
        context[id].guard = &guard;

        int status = pthread_create(&context[id].descriptor, 0, _boast, &context[id]);
        if (status) {
            throw("error in pthread_create");
        }
        
    }

    // and harvest them
    for (size_t id = 0; id < threads; id++) {
        pthread_join(context[id].descriptor, 0);
    }

    // destroy the mutex
    pthread_mutex_destroy(&mutex);

    // all done
    return 0;
}

// end of file
