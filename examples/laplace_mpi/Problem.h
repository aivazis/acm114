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

#if !defined(acm114_laplace_Problem_h)
#define acm114_laplace_Problem_h

namespace acm114 {
    namespace laplace {
        class Problem;
    }
}

#include "Grid.h"
#include <string>
#include <mpi.h>

// the solution representation
class acm114::laplace::Problem {
    //typedefs
public:
    typedef std::string string_t;

    // interface
public:
    string_t name() const;
    inline MPI_Comm communicator() const;
    inline int rank() const;

    // access to my grid
    inline Grid & solution();
    inline const Grid & solution() const;
    // interface used by the solver
    virtual void initialize();
    virtual void applyBoundaryConditions() = 0;

    // meta methods
public:
    Problem(string_t name, double interval, int processors, size_t points);
    virtual ~Problem();

    // data members
protected:
    string_t _name;
    double _delta;
    double _x0, _y0;
    int _rank, _size;
    int _processors;
    int _place[2];
    MPI_Comm _cartesian;

    Grid _solution;

    // disable these
private:
    Problem(const Problem &);
    const Problem & operator= (const Problem &);
};

// get the inline definitions
#define acm114_laplace_Problem_icc
#include "Problem.icc"
#undef acm114_laplace_Problem_icc

#endif

// end of file
