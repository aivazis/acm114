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
#include <fstream>
#include <iostream>

// forward declarations
class Grid;
class Visualizer;

void initialize(Grid & grid);
void laplace(Grid & grid, double tolerance);

// the solution representation
class Grid {
public:
    // interface: TBD

    // meta methods
public:
    Grid(size_t size);
    ~Grid();

    // disabled interface
    // grid will own dynamic memory, so don't let the compiler screw up
private:
    Grid(const Grid &);
    const Grid & operator= (const Grid &);
};

// the grid implementation
Grid::Grid(size_t size) {
}

Grid::~Grid() {
}

// the visualizer class
class Visualizer {
public:
    // local type aliases
    typedef std::ostream stream_t;

    // interface
public:
    void csv(const Grid & grid, stream_t & stream);

    // meta methods
public:
    inline Visualizer() {}
};

// the Visualizer class implementation
void Visualizer::csv(const Grid & grid, Visualizer::stream_t & stream) {
    return;
}

// the grid initializer 
void initialize(Grid & grid) {
    return;
}

// the solver driver
void laplace(Grid & grid, double tolerance) {
    return;
}

// main program
int main(int argc, char* argv[]) {
    // default values for our user configurable settings
    long N = 10;
    double tolerance = 1.0e-6;
    const char* filename = "laplace.csv";
    // read the command line
    int command;
    while ((command = getopt(argc, argv, "N:e:o:")) != -1) {
        switch (command) {
        // get the convergence tolerancae
        case 'e':
            tolerance = atof(optarg);
            break;
        // get the grid size
        case 'N':
            N = (long) atof(optarg);
            break;
        // get the name of the output file
        case 'o':
            filename = optarg;
        }
    }
    
    // allocate space for the solution
    Grid potential(N);

    // initialize and apply our boundary conditions
    initialize(potential);

    // call the solver
    laplace(potential, tolerance);

    // open a stream to hold the answer
    std::fstream output(filename, std::ios_base::out);

    // build a visualizer and render the solution in our chosen format
    Visualizer visualizer;
    visualizer.csv(potential, output);

    // all done
    return 0;
}

// end of file
