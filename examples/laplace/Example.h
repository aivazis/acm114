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

#include "Problem.h"

// namespace
namespace acm114 {
    namespace laplace {
        class Example;
    }
}

// the example problem from the lectures
class acm114::laplace::Example : public acm114::laplace::Problem {
    // interface
public:
    virtual void initialize();
    virtual void initialize(Grid &) const;

    // meta methods
public:
    inline Example(string_t name, double width, size_t points);
    virtual ~Example();

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
