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
#include <cmath>

#include "Example.h"

using namespace acm114::laplace;

const double pi = M_PI;

// destructor
Example::~Example() {}

// boundary conditions
void Example::applyBoundaryConditions() {
    // a reference to my grid
    Grid & g = _solution;
    // my rank;
    int rank = _rank;
    // the ranks of my four neighbors
    int top, right, bottom, left;
    // get them
    MPI_Cart_shift(_cartesian, 1, 1, &rank, &top);
    MPI_Cart_shift(_cartesian, 0, 1, &rank, &right);
    MPI_Cart_shift(_cartesian, 1, -1, &rank, &bottom);
    MPI_Cart_shift(_cartesian, 0, -1, &rank, &left);
    // print them
    // std::cout
        // << _rank << " at (" << _place[0] << "," << _place[1] << "):"
        // << " top: " << top
        // << ", right: " << right
        // << ", bottom: " << bottom
        // << ", left: " << left
        // << std::endl;

    // allocate send and receive buffers
    double * sendbuf = new double[g.size()];
    double * recvbuf = new double[g.size()];

    // shift to the right
    // fill my sendbuf with my RIGHT DATA BORDER
    for (size_t cell=0; cell < g.size(); cell++) {
        sendbuf[cell] = g(g.size()-2, cell); 
    }
    // do the shift 
    MPI_Sendrecv(
                 sendbuf, g.size(), MPI_DOUBLE, right, 17,
                 recvbuf, g.size(), MPI_DOUBLE, left, 17,
                 _cartesian, MPI_STATUS_IGNORE
                 );
    if (left == MPI_PROC_NULL) {
        // if i am on the boundary, paint the dirichlet conditions
        for (size_t cell=0; cell < g.size(); cell++) {
            g(0, cell) = 0;
        }
    } else {
        // fill my LEFT FRINGE with the received data
        for (size_t cell=0; cell < g.size(); cell++) {
            g(0, cell) = recvbuf[cell];
        }
    }

    // shift to the left
    // fill my sendbuf with my LEFT DATA BORDER
    for (size_t cell=0; cell < g.size(); cell++) {
        sendbuf[cell] = g(1, cell);
    }
    // do the shift 
    MPI_Sendrecv(
                 sendbuf, g.size(), MPI_DOUBLE, left, 17,
                 recvbuf, g.size(), MPI_DOUBLE, right, 17,
                 _cartesian, MPI_STATUS_IGNORE
                 );
    if (right == MPI_PROC_NULL) {
        // if i am on the boundary, paint the dirichlet conditions
        for (size_t cell=0; cell < g.size(); cell++) {
            g(g.size()-1, cell) = 0;
        }
    } else {
        // fill my RIGHT FRINGE with the received data
        for (size_t cell=0; cell < g.size(); cell++) {
            g(g.size()-1, cell) = recvbuf[cell];
        }
    }
    
    // shift up
    // fill my sendbuf with my TOP DATA BORDER
    for (size_t cell=0; cell < g.size(); cell++) {
        sendbuf[cell] = g(cell, g.size()-2);
    }
    // do the shift
    MPI_Sendrecv(
                 sendbuf, g.size(), MPI_DOUBLE, top, 17,
                 recvbuf, g.size(), MPI_DOUBLE, bottom, 17,
                 _cartesian, MPI_STATUS_IGNORE
                 );
    if  (bottom == MPI_PROC_NULL) {
        // if i am on the boundary, paint the dirichlet conditions
        for (size_t cell=0; cell < g.size(); cell++) {
            g(cell, 0) = std::sin((_x0 + cell*_delta)*pi);
        }
    } else {
        // fill my BOTTOM FRINGE with the received data
        for (size_t cell=0; cell < g.size(); cell++) {
            g(cell, 0) = recvbuf[cell];
        }
    }

    // shift down
    // fill my sendbuf with my BOTTOM DATA BORDER
    for (size_t cell=0; cell < g.size(); cell++) {
        sendbuf[cell] = g(cell, 1);
    }
    // do the shift
    MPI_Sendrecv(
                 sendbuf, g.size(), MPI_DOUBLE, bottom, 17,
                 recvbuf, g.size(), MPI_DOUBLE, top, 17,
                 _cartesian, MPI_STATUS_IGNORE
                 );
    if  (top == MPI_PROC_NULL) {
        // if i am on the boundary, paint the dirichlet conditions
        for (size_t cell=0; cell < g.size(); cell++) {
            g(cell, g.size()-1) = std::sin((_x0 + cell*_delta)*pi) * std::exp(-pi);
        }
    } else {
        // fill my TOP FRINGE with the received data
        for (size_t cell=0; cell < g.size(); cell++) {
            g(cell, g.size()-1) = recvbuf[cell];
        }
    }
    
    return;
}

// end of file
