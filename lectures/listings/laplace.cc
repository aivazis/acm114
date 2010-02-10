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
#include <cstdlib>
#include <fstream>
#include <iostream>

// constants
const double pi = M_PI;

// forward declarations
class Grid;
class Visualizer;

void exact(Grid & grid);
void initialize(Grid & grid);
void laplace(Grid & grid, double tolerance);

// the solution representation
class Grid {
    // interface
public:
    // zero out all cells
    void clear(double value=0.0);
    // the grid dimensions
    size_t size() const { return _size; }
    // the grid spacing
    double delta() const { return _delta; }
    // access to the cells
    double & operator()(size_t i, size_t j) { return _block[j*_size+i]; }
    double operator()(size_t i, size_t j) const { return _block[j*_size+i]; }
    // exchange the data blocks of two compatible grids
    static void swapBlocks(Grid &, Grid &);
    // meta methods
public:
    Grid(size_t size);
    ~Grid();
    // data members
private:
    const size_t _size;
    const double _delta;
    double* _block;
    // disable these
private:
    Grid(const Grid &);
    const Grid & operator= (const Grid &);
};

// the grid implementation
// interface
void Grid::clear(double value) {
    for (size_t i=0; i < _size*_size; i++) {
        _block[i] = value;
    }

    return;
}

void Grid::swapBlocks(Grid & g1, Grid & g2) {
    // bail outif the two operands are not compatible
    if (g1.size() != g2.size()) {
        throw "Grid::swapblocks: size mismatch";
    }
    if (g1.delta() != g2.delta()) {
        throw "Grid::swapblocks: spacing mismatch";
    }
    // but if they are, just exhange their data buffers
    double * temp = g1._block;
    g1._block = g2._block;
    g2._block = temp;
    // all done
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
    grid.clear(1.0);

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

void exact(Grid & grid) {
    //  paint the exact solution
    for (size_t j=0; j < grid.size(); j++) {
        for (size_t i=0; i < grid.size(); i++) {
            double x = i*grid.delta();
            double y = j*grid.delta();
            grid(i,j) = std::exp(-pi*y)*std::sin(pi*x);
        }
    }
    return;
}

void relative_error(const Grid & computed, const Grid & exact, Grid & error) {
    //  compute the relative error
    for (size_t j=0; j < exact.size(); j++) {
        for (size_t i=0; i < exact.size(); i++) {
            if (exact(i,j) == 0.0) {
                error(i,j) = std::abs(computed(i,j));
            } else {
                error(i,j) = std::abs(computed(i,j) - exact(i,j))/exact(i,j);
            }
        }
    }
    return;
}

// the solver driver
void laplace(Grid & current, double tolerance) {
    std::cout << "laplace:" << std::endl;

    // create and initialize temporary storage
    Grid next(current.size());
    initialize(next);

    // put an upper bound on the number of iterations
    long max_iterations = (long) (1./tolerance);
    for (long iterations = 0; iterations<max_iterations; iterations++) {
        if (iterations%50 == 0) {
            std::cout << "     " << iterations << std::endl;
        }
        double max_dev = 0.0;
        // do an iteration step
        // leave the boundary alone
        // iterate over the interior of the grid
        for (size_t j=1; j < current.size()-1; j++) {
            for (size_t i=1; i < current.size()-1; i++) {
                next(i,j) = 0.25*(current(i+1,j)+current(i-1,j)+current(i,j+1)+current(i,j-1));
                // compute the deviation from the last generation
                double dev = std::abs(next(i,j) - current(i,j));
                // and update the maximum deviation
                if (dev > max_dev) {
                    max_dev = dev;
                }
            }
        }
        // swap the blocks between the two grids
        Grid::swapBlocks(current, next);
        // check covergence
        if (max_dev < tolerance) {
            std::cout << " ### convergence in " << iterations << " iterations!" << std::endl;
            break;
        }
    }

    std::cout << " --- done." << std::endl;
    return;
}


// main program
int main(int argc, char* argv[]) {
    // default values for our user configurable settings
    size_t N = 9;
    double tolerance = 1.0e-3;
    const char* filename = "laplace.csv";
    // read the command line
    int command;
    while ((command = getopt(argc, argv, "N:e:o:")) != -1) {
        switch (command) {
        // get the convergence tolerance
        case 'e':
            tolerance = atof(optarg);
            break;
        // get the grid size
        case 'N':
            N = (size_t) atof(optarg);
            break;
        // get the name of the output file
        case 'o':
            filename = optarg;
        }
    }

    // build a visualizer
    Visualizer vis;

    // compute the exact solution
    Grid solution(N);
    exact(solution);
    std::fstream exact_stream("exact.csv", std::ios_base::out);
    vis.csv(solution, exact_stream);
    
    // allocate space for the solution
    Grid potential(N);
    // initialize and apply our boundary conditions
    initialize(potential);
    // call the solver
    laplace(potential, tolerance);
    // open a stream to hold the answer
    std::fstream output_stream(filename, std::ios_base::out);
    // build a visualizer and render the solution in our chosen format
    vis.csv(potential, output_stream);

    // compute the error field
    Grid error(N);
    relative_error(potential, solution, error);
    std::fstream error_stream("error.csv", std::ios_base::out);
    vis.csv(error, error_stream);

    // all done
    return 0;
}

// end of file
