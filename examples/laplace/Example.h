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

#if !defined(acm114_laplace_Example_h)
#define acm114_laplace_Example_h

namespace acm114 {
    namespace laplace {
        class Example;
        class Grid;
        class Problem;
    }
}

#include "Problem.h"

// the example problem from the lectures
class acm114::laplace::Example : public acm114::laplace::Problem {
    // interface
public:
    virtual void initialize(Grid & grid);

    // meta methods
public:
    inline Example(double delta);
    virtual ~Example();

    // data members
private:
    double _delta;

    // disable these
private:
    Example(const Example &);
    const Example & operator= (const Example &);
};

// get the inline definitions
#define acm114_laplace_Example_icc
#include "Example.icc"
#undef acm114_laplace_Example_icc

#endif

// end of file
