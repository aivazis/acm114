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
#include <cmath>
#include <iostream>
#include <iomanip>

// the smallest z we allow
const int EPSILON = 1.0e-17;
const double pi = 4*std::atan(1.0);
// dilog
double dilog(double z, long N) {
    // abort if N < 1
    if (N < 1) {
        throw "the number of subdivisions must be positive";
    }
    // abort for z > 1 to avoid dealing with the imaginary part
    if (z > 1.0) {
        throw "math domain error: z > 1";
    }
    // for really small values, return a quick approximation
    if (std::abs(z) < EPSILON) {
        return z;
    }
    // initialize
    double dx = z/N;
    double dilog = 0;
    // loop
    for (double x=dx/2; x < z; x+=dx) {
        dilog += dx * std::log(1-x)/x;
    }
    // return; don't forget the sign
    return -dilog;
}

// main program
int main(int argc, char* argv[]) {

    try {
        double value = dilog(1e-12, 10*1000*1000);
        double exact = pi*pi/6;
        double error = std::abs(exact-value)/exact;
        std::cout
            << std::setprecision(17)
            << "Li2(1)=" << value 
            << ", exact value: " << exact
            << std::setiosflags(std::ios_base::scientific) << ", error: " << error
            << std::endl;
    } catch (const char * message) {
        std::cout << "dilog error: " << message << std::endl;
    };
    return 0;
}

// end of file
