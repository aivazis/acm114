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

// the solution representation
class acm114::laplace::Problem {
    //typedefs
public:
    typedef std::string string_t;

    // interface
public:
    void csv(string_t seed) const;

    inline const Grid & exact() const;

    inline Grid & solution();
    inline const Grid & solution() const;

    inline Grid & error();
    inline const Grid & error() const;

    // abstract
    virtual void initialize() = 0;
    virtual void initialize(Grid &) const = 0;

    // meta methods
public:
    inline Problem(double width, size_t points);
    virtual ~Problem();

    // data members
protected:
    double _delta;
    Grid _solution;
    Grid _exact;
    Grid _error;
    Grid _deviation;

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
