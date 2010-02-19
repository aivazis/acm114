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

#if !defined(acm114_laplace_Jacobi_h)
#define acm114_laplace_Jacobi_h

#include "Solver.h"

namespace acm114 {
    namespace laplace {
        class Jacobi;
    }
}

#include <cstdlib>

// the solution representation
class acm114::laplace::Jacobi : public acm114::laplace::Solver {
    // interface
public:
    virtual void solve(Problem &);

    // meta methods
public:
    inline Jacobi(double tolerance, size_t workers);
    virtual ~Jacobi();

    // implementation details
protected:
    virtual void _solve(Problem &);
    static void * _update(void *);

    // data members
private:
    double _tolerance;
    size_t _workers;

    // disable these
private:
    Jacobi(const Jacobi &);
    const Jacobi & operator= (const Jacobi &);
};

// get the inline definitions
#define acm114_laplace_Jacobi_icc
#include "Jacobi.icc"
#undef acm114_laplace_Jacobi_icc

#endif

// end of file
