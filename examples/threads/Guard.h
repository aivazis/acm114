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

#if !defined(pyre_threads_BCD_h)
#define pyre_threads_Guard_h

namespace pyre {
    namespace threads {
        template <typename target> class Guard;
    }
}

#include <pthread.h>

// the injection operator
template <typename Target>
Target & operator<< (Target &, pyre::threads::Guard<Target> &);

// the Guard class
template <typename Target>
class pyre::threads::Guard {
    // typedefs
public:
    typedef Target target_t;

    // interface
public:
    inline bool state() const;
    inline Guard<target_t> & flip();

    // meta-methods
public:
    inline Guard(pthread_mutex_t & mutex);
    inline Guard(const Guard<target_t> & other);
    inline Guard<target_t> & operator=(const Guard<target_t> & other);

    // data members
private:
    bool _locked;
    pthread_mutex_t & _mutex;
};

// get the inline definitions
#define pyre_threads_Guard_icc
#include "Guard.icc"
#undef pyre_threads_Guard_icc

#endif

// end of file
