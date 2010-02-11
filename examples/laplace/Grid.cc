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
#include <cstdlib>

#include "Grid.h"

void Grid::swapBlocks(Grid & g1, Grid & g2) {
    // bail out if the two operands are not compatible
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

// destructor
Grid::~Grid() {
    delete [] _block;
}

// end of file
