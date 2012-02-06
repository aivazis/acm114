// -*- C++ -*-
// michael a.g. aivazis
// california institute of technology
// (c) 1998-2012 all rights reserved
//

#include <getopt.h> // for getopt and friends
#include <pthread.h>

#include <cstdio>
#include <cstdlib>  // for atof
#include <cmath>

#include <map>
#include <iostream>
#include <iomanip>


// shared information
struct problem {
    int workers;           // total number of threads
    double dz;             // the width of each subdivision
    double sum;            // storage for the partial computations

    pthread_mutex_t lock;  // mutex to control access to the sum
};

// thread specific information
struct context {
    // thread info
    int id;
    pthread_t descriptor;
    // the workload for this thread
    long subdivisions;  // number of subdivisions
    double z_low;       // the lower limit of integration
    double partial;     // record the partial sum computed by this thread
    // the shared problem information
    problem* info;
};

// worker
void* worker(void* arg) {
    context* ctxt = (context *) arg;
    // pull the problem information from the thread context
    double dz = ctxt->info->dz;
    double z = ctxt->z_low + dz/2;
    // loop over the subdivisions assigned to this thread
    double sum = 0.0;
    for (long i=0; i < ctxt->subdivisions; i++) {
        sum += std::log(1-z)/z;
        z += dz;
    }
    // multiply by the width of each subdivision and adjust the sign
    sum *= -dz;

    // grab the lock
    pthread_mutex_lock(&(ctxt->info->lock));
    // store the result
    ctxt->info->sum += sum;
    // and release the lock
    pthread_mutex_unlock(&(ctxt->info->lock));

    // all done
    return 0;
}

// driver
double dilog(double z, long N, int threads) {
    // the width of each interval subdivision
    const double dz = z/N;

    // setup the problem context
    problem info;
    info.workers = threads;
    info.dz = dz;
    info.sum = 0.0;
    pthread_mutex_init(&info.lock, 0);

    // and an array to hold the thread contexts
    context thr_info[threads];
    // partition the number of subdivisions
    long nominal_load = N/threads;

    // spawn the workers
    for (int tid=0; tid<threads; tid++) {
        // store the thread id
        thr_info[tid].id = tid;
        // point to the shared problem info
        thr_info[tid].info = &info;

        // compute the starting point of the partial integral
        thr_info[tid].z_low = tid*nominal_load*dz;
        // compute the number of subdivisions for this thread
        if (tid == threads - 1) {
            // the last thread gets the leftovers
            thr_info[tid].subdivisions = N - tid*nominal_load;
        } else {
            thr_info[tid].subdivisions = nominal_load;
        }

        // create the thread
        int status = pthread_create(
            &(thr_info[tid].descriptor), 0, worker, &thr_info[tid]);
        if (status) {
            printf("error %d in pthread_create\n", status);
        }
    }

    // harvest the threads
    for (int tid=0; tid<threads; tid++) {
        pthread_join(thr_info[tid].descriptor, 0);
    }

    // all done
    return info.sum;
}

// main program
int main(int argc, char* argv[]) {
    //  default values for the command line options
    long N = 1000;
    double z = 1.0;
    int threads = 8;

    // read the command line
    int command;
    while ((command = getopt(argc, argv, "z:N:t:")) != -1) {
        switch (command) {
        case 'z':
            // get the argument of the dilogarithm 
            z = atof(optarg);
            break;
        case 'N':
            // get the number of subdivisions
            N = (long) atof(optarg);
            break;
        case 't':
            // get the numberof threads
            threads = atoi(optarg);
            break;
        }
    }

    // error checking
    // abort if N < 1
    if (N < 1) {
        std::cout 
            << "the number of subdivisions must be positive"
            << std::endl;
        return 0;
    }

    // abort for z > 1 to avoid dealing with the imaginary part
    if (z > 1.0) {
        std::cout << "math domain error: z > 1" << std::endl;
        return 0;
    } 

    // compute
    double value = dilog(z, N, threads);

    // build a database of the known dilogarithm values
    const double pi = M_PI;
    std::map<double, double> answers;
    answers[1.0] = pi*pi/6;
    answers[-1.0] = -pi*pi/12;

    // print out the value
    std::cout << "Li2(" << z << ")="
         << std::setprecision(17) << std::endl
         << " computed: " << value << std::endl;
    // check whether we know the right answer
    std::map<double,double>::const_iterator lookup = answers.find(z);
    if (lookup != answers.end()) {
        // and if we do, print it out
        double exact = lookup->second;
        std::cout << "    exact: " << exact << std::endl;
        // compute the approximation error and print it out
        double error = std::abs(exact-value)/exact;
        std::cout 
            << std::setiosflags(std::ios_base::scientific) 
            << "    error: " << error << std::endl;
    }

    return 0;
}

// end of file
