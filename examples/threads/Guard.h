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

#if !defined(pyre_threads_Guard_h)
#define pyre_threads_Guard_h

namespace pyre {
    namespace threads {
        class Guard;
    }
}

#include <pthread.h>

class pyre::threads::Guard {
public:
    typedef pthread_mutex_t mutex_t;
    typedef std::ostream ostream_t;
    typedef ostream_t & (*behavior_t)(ostream_t &, mutex_t & mutex);

public:
    friend ostream_t & operator<< (ostream_t &, Guard &);

public:
    inline static ostream_t & lock(ostream_t & stream, mutex_t & mutex);
    inline static ostream_t & unlock(ostream_t & stream, mutex_t & mutex);

    // meta methods
public:
    inline Guard(behavior_t f, mutex_t & m);

    inline Guard(const Guard & g);
    Guard & operator= (const Guard & g);

    // data members
public:
    behavior_t _f;
    mutex_t & _m;
};

// the injection operator
inline std::ostream & operator<< (std::ostream & str, pyre::threads::Guard g);

// the two manipulators
inline pyre::threads::Guard lock(pthread_mutex_t & mutex);
inline pyre::threads::Guard unlock(pthread_mutex_t & mutex);

// get the inline definitions
#define pyre_threads_Guard_icc
#include "Guard.icc"
#undef pyre_threads_Guard_icc

#endif

// end of file
