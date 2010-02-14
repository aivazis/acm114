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

#if !defined(pyre_timers_Timer_h)
#define pyre_timers_Timer_h

namespace pyre {
    namespace timers {
        class Timer;
    }
}

// imported types
#include <string>
#if defined(__config_platform_darwin)
#include "mach/Clock.h"
#elif defined(__config_platform_linux)
#include "posix/Clock.h"
#endif

// the solution representation
class pyre::timers::Timer {
    //typedefs
public:
    typedef Clock clock_t;
    typedef std::string name_t;
    typedef Timer timer_t;

    // interface
public:
    inline name_t name() const;

    inline void start();
    inline void stop();
    inline void reset();

    inline double lap();  // read the elapsed time 
    inline double read(); // return the accumulated time 

    // meta methods
public:
    inline Timer(name_t name);
    virtual ~Timer();

    // data members
private:
    name_t _name;
    clock_t::tick_t _start;
    clock_t::tick_t _accumulated;

    static clock_t _theClock;

    // disable these
private:
    Timer(const Timer &);
    const timer_t & operator= (const timer_t &);
};

// get the inline definitions
#define pyre_timers_Timer_icc
#include "Timer.icc"
#undef pyre_timers_Timer_icc

#endif

// end of file
