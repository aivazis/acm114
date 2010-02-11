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

#if !defined(acm114_laplace_Grid_h)
#define acm114_laplace_Grid_h

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
    inline Grid(size_t size);
    virtual ~Grid();
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

// get the inline definitions
#define acm114_laplace_Grid_icc
#include "Grid.icc"
#undef acm114_laplace_Grid_icc

#endif

// end of file
