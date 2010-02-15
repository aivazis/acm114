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

#if !defined(pyre_timers_BCD_h)
#define pyre_timers_BCD_h

namespace pyre {
    namespace timers {
        template <size_t scale> class BCD;
    }
}

// operators on BCDs
// binary +
template <size_t scale>
pyre::timers::BCD<scale> operator+ (
    const pyre::timers::BCD<scale> &, const pyre::timers::BCD<scale> &);
// unary -
template <size_t scale>
pyre::timers::BCD<scale> operator- (const pyre::timers::BCD<scale> &);

// binary -
template <size_t scale>
pyre::timers::BCD<scale> operator- (
    const pyre::timers::BCD<scale> &, const pyre::timers::BCD<scale> &);

// the BCD class
template <size_t scale>
class pyre::timers::BCD {
    // external operators
public:
    friend BCD<scale> operator+ <>(const BCD<scale> &, const BCD<scale> &);
    friend BCD<scale> operator- <>(const BCD<scale> &);
    friend BCD<scale> operator- <>(const BCD<scale> &, const BCD<scale> &);

    // interface
public:
    inline BCD<scale> & operator+= (const BCD<scale> &);
    inline BCD<scale> & operator-= (const BCD<scale> &);

    // convert to double
    operator double () const;


    // meta methods
public:
    inline ~BCD();

    inline BCD(size_t msw=0, size_t lsw=0);
    BCD(const BCD &);
    const BCD & operator= (const BCD &);

    // data members
private:
    size_t _msw;
    size_t _lsw;

    static const int _scale = scale;

    // disable these
private:
};

// get the inline definitions
#define pyre_timers_BCD_icc
#include "BCD.icc"
#undef pyre_timers_BCD_icc

#endif

// end of file
