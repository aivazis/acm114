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
    inline string_t name() const;

    inline const Grid & exact() const;
    inline const Grid & deviation() const;

    inline Grid & solution();
    inline const Grid & solution() const;

    inline Grid & error();
    inline const Grid & error() const;

    // abstract
    virtual void initialize() = 0;
    virtual void initialize(Grid &) const = 0;

    // meta methods
public:
    inline Problem(string_t name, double width, size_t points);
    virtual ~Problem();

    // data members
protected:
    string_t _name;
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
