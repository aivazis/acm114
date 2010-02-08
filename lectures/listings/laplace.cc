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
#include <cmath>
#include <fstream>
#include <iostream>

// constants
const double pi = M_PI;

// forward declarations
class Grid;
class Visualizer;

void initialize(Grid & grid);
void laplace(Grid & grid, double tolerance);

// the solution representation
class Grid {
    // interface
public:
    // zero out all cells
    void clear();
    // the grid dimensions
    size_t size() const { return _size; }
    // the grid spacing
    double delta() const { return _delta; }
    // access to the cells
    double & operator()(size_t i, size_t j) { return _block[j*_size+i]; }
    double operator()(size_t i, size_t j) const { return _block[j*_size+i]; }
    // meta methods
public:
    Grid(size_t size);
    ~Grid();
    // data members
private:
    const size_t _size;
    const double _delta;
    double* _block;
    // disabled interface
    // grid will own dynamic memory, so don't let the compiler screw up
private:
    Grid(const Grid &);
    const Grid & operator= (const Grid &);
};

// the grid implementation
// interface
void Grid::clear() {
    for (size_t i=0; i < _size*_size; i++) {
        _block[i] = 0.0;
    }

    return;
}

// constructor
Grid::Grid(size_t size) :
    _size(size), 
    _delta((1.0 - 0.0)/(size-1)),
    _block(new double[size*size]) {
}

// destructor
Grid::~Grid() {
    delete [] _block;
}

// the visualizer class
class Visualizer {
    // local type aliases
public:
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
    for (size_t j=0; j < grid.size(); j++) {
        stream << j;
        for (size_t i=0; i < grid.size(); i++) {
            stream << "," << grid(i,j);
        }
        stream << std::endl;
    }

    return;
}

// the grid initializer: zero out and apply our boundary conditions 
void initialize(Grid & grid) {
    // ask the grid to clear its memory
    grid.clear();

    // compute the cell spacing
    const double delta = (1.0 - 0.0) / (grid.size() - 1);

    // apply the dirichlet conditions
    for (size_t cell=0; cell < grid.size(); cell++) {
        // evaluate sin(pi x)
        double sin = std::sin(cell * grid.delta() * pi);
        // along the x axis, at top and  bottom
        grid(cell, 0) = sin;
        grid(cell, grid.size()-1) = sin * std::exp(-pi);
        // along the y axis, left and right
        grid(0, cell) = 0.0;
        grid(grid.size()-1, cell) = 0.0;
    }

    return;
}

// the solver driver
void laplace(Grid & grid, double tolerance) {
    return;
}

// main program
int main(int argc, char* argv[]) {
    // default values for our user configurable settings
    long N = 9;
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
