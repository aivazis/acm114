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

#if !defined(pyre_timers_Display_h)
#define pyre_timers_Display_h

namespace pyre {
    namespace timers {
        class Display;
    }
}

// imported types
#include <string>
#include "Timer.h"
#include "Registrar.h"

// declaration
class pyre::timers::Display {
    // types
public:
    typedef std::string name_t;
    typedef Timer timer_t;
    typedef pyre::Registrar<timer_t> index_t;

    // interface
public:
    name_t name() const;
    // start a timer
    Display & start();
    // stop a timer
    Display & stop();
    // zero out a timer
    Display & reset();

    // take a reading in seconds from a *running* timer 
    double lap();
    // get the number of seconds accumulated by a *stopped* timer
    double read();

    // meta methods
public:
    virtual ~Display();
    inline Display(name_t name);

    // data members
private:
    timer_t & _timer;

    static index_t _index;

    // implementation details
private:
    static timer_t & _findTimer(name_t name);
};

// get the inline definitions
#define pyre_timers_Display_icc
#include "Display.icc"
#undef pyre_timers_Display_icc

#endif

// end of file
