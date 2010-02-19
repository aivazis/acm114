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

namespace acm114 {
    namespace laplace {
        class Grid;
    }
}

#include <cstdlib>

// the solution representation
class acm114::laplace::Grid {
    // interface
public:
    // zero out all cells
    void clear(double value=0.0);
    // the grid dimensions
    inline size_t size() const; 

    // access to the cells
    inline double & operator()(size_t i, size_t j); 
    inline double operator()(size_t i, size_t j) const;

    // exchange the data blocks of two compatible grids
    static void swapBlocks(Grid &, Grid &);

    // meta methods
public:
    inline Grid(size_t size);
    virtual ~Grid();
    // data members

private:
    const size_t _size;
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
