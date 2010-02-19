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

#if !defined(acm114_laplace_Solver_h)
#define acm114_laplace_Solver_h

namespace acm114 {
    namespace laplace {
        class Solver;
        class Problem;
    }
}

// the solution representation
class acm114::laplace::Solver {
    // interface
public:
    virtual void solve(Problem &) = 0;

    // meta methods
public:
    inline Solver();
    virtual ~Solver();

    // data members
private:

    // disable these
private:
    Solver(const Solver &);
    const Solver & operator= (const Solver &);
};

// get the inline definitions
#define acm114_laplace_Solver_icc
#include "Solver.icc"
#undef acm114_laplace_Solver_icc

#endif

// end of file
