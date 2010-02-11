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
        class Grid;
        class Problem;
    }
}

// the solution representation
class acm114::laplace::Problem {
    // interface
public:
    virtual void initialize(Grid & grid) = 0;

    // meta methods
public:
    inline Problem();
    virtual ~Problem();

    // data members
private:

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
