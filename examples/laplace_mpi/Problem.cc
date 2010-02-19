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

#include <portinfo>
#include "Problem.h"

using namespace acm114::laplace;

#include <sstream>

// interface
Problem::string_t acm114::laplace::Problem::name() const {
    std::stringstream s;
    s << _name << "-" << _place[0] << "x" << _place[1];
    return s.str();
}

// constructor
Problem::Problem(
    string_t name, double interval, int processors, size_t points) :
    _name(name),
    _delta(interval/((points-2)*processors+1)),
    _rank(0), _size(0), _processors(processors), _place(),
    _cartesian(),
    _solution(points) {

    // build the intended layout
    int layout[] = { processors, processors };
    // find my rank in the world communicator
    int worldRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    // build a Cartesian communicator
    int periods[] = { 0, 0 };
    MPI_Cart_create(MPI_COMM_WORLD, 2, &layout[0], periods, 1, &_cartesian);
    // check whether i can paritcipate
    if (_cartesian != MPI_COMM_NULL) {
        // get my rank in the cartesian communicator
        MPI_Comm_rank(_cartesian, &_rank);
        MPI_Comm_size(_cartesian, &_size);
        // get my logical position on the process grid
        MPI_Cart_coords(_cartesian, _rank, 2, &_place[0]);
        
        // everybody prints out their cartesian rank and place
        std::cout
            << "world rank " << worldRank << ": now "
            << _rank << " at (" << _place[0] << "," << _place[1] << "):"
            << " n=" << points << ", delta=" << _delta
            << std::endl;
    } else {
        // i was left out because the total number of processors is not a square
        std::cout
            << "world rank " << worldRank << ": not a member of the cartesian communicator "
            << std::endl;
    }
}

// destructor
Problem::~Problem() {}

// end of file
