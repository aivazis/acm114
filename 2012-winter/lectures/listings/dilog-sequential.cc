// -*- C++ -*-
// michael a.g. aivazis
// california institute of technology
// (c) 1998-2012 all rights reserved
//

#include <getopt.h> // for getopt and friends
#include <cstdlib>  // for atof
#include <cmath>    // for the correct abs, log

#include <map> // for our misguided results database
#include <iostream>
#include <iomanip>

// dilog
double dilog(double z, long N) {
    // initialize
    double dx = z/N;
    double x = dx/2;
    double sum = 0;
    // loop
    for (long i=0; i < N; i++) {
        sum += std::log(1-x)/x;
        x += dx;
    }
    // return; don't forget the sign
    return -dx * sum;
}

// main program
int main(int argc, char* argv[]) {
    //  default values for the command line options
    long N = 1000;
    double z = 1.0;

    // read the command line
    int command;
    while ((command = getopt(argc, argv, "z:N:")) != -1) {
        switch (command) {
        // get the argument of the dilogarithm 
        case 'z':
            z = atof(optarg);
            break;
        // get the number of subdivisions
        case 'N':
            N = (long) atof(optarg);
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
    double value = dilog(z, N);

    // build a database of the known dilogarithm values
    // this is a bit naive; why?
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
