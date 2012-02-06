// -*- C++ -*-
// 
// michael a.g. aïvázis
// california institute of technology
// (c) 1998-2012 all rights reserved
// 

#include <getopt.h> // for getopt and friends
#include <mpi.h>

#include <cstdio>
#include <cstdlib>  // for atof
#include <cmath>

#include <map>
#include <iostream>
#include <iomanip>

double dilog(double zprime, long N, int id, int processes) {
    // the width of each interval subdivision
    const double dz = zprime/N;
    // compute the starting point of the partial integral
    const double z_low = id*zprime/processes;
    // partition the number of subdivisions
    long nominal_load = N/processes;
    // the last process gets the leftovers
    if (id == processes - 1) {
        nominal_load = N - id*nominal_load;
    }
    // initialize the partial sum
    double sum = 0.0;
    double z = z_low + dz/2;
    // loop over the subdivisions assigned to this thread
    for (long i=0; i < nominal_load; i++)  {
        sum += std::log(1-z)/z;
        z += dz;
    }
    // collect the partial answers from all the processes
    double value;
    MPI_Allreduce(&sum, &value, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    // multiply by the width of each subdivision and adjust the sign
    return -dz*value;
}

// main program
int main(int argc, char* argv[]) {
    // initialize MPI
    int status = MPI_Init(&argc, &argv);
    if (status != MPI_SUCCESS) {
        std::cout << "error in MPI_Init; aborting..." << std::endl;
        return status;
    }
    // get process information from the world communicator
    int id, processes;
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);

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

    // error checking
    // abort if N < 1
    if (N < 1) {
        if (id == 0) {
            std::cout 
                << "the number of subdivisions must be positive"
                << std::endl;
        }
        MPI_Finalize();
        return 0;
    }
    // abort for z > 1 to avoid dealing with the imaginary part
    if (z > 1.0) {
        if (id == 0) {
            std::cout << "math domain error: z > 1" << std::endl;
        }
        MPI_Finalize();
        return 0;
    } 
    // compute
    double value = dilog(z, N, id, processes);
    if (id != 0) { // let all but processor 0 die
        // shut down MPI
        MPI_Finalize();
        return 0;
    }

    // build a database of the known dilogarithm values
    const double pi = M_PI;
    std::map<double, double> answers;
    answers[1.0] = pi*pi/6;
    answers[-1.0] = -pi*pi/12;

    // print out the value
    std::cout << "Li2(" << z << ")=" << std::setprecision(17) << std::endl;
    std::cout << " computed: " << value << std::endl;
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

    // shut down MPI
    MPI_Finalize();
    return 0;
}

// end of file
