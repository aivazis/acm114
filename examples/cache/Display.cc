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

#include <portinfo>

#include "Display.h"

// imported types
#include <pthread.h>

pthread_mutex_t _indexLock;
static int status = pthread_mutex_init(&_indexLock, 0);

using namespace pyre::timers;

// the map
Display::index_t Display::_index;

// lookup a timer in the index and return it 
Display::timer_t & Display::_findTimer(name_t name) {
    // 
    // lookup <name> in the _index and return the associated timer
    // if not found, create a new one and index it under <name>
    //
    timer_t * timer;
    // lock the container
    pthread_mutex_lock(&_indexLock);
    // try to find the timer associated with this name in the index
    index_t::iterator lookup = _index.find(name);
    // if it's there grab it; otherwise build a new and add itto the container
    if (lookup != _index.end()) {
        timer = lookup->second;
    } else {
        timer = new timer_t(name);
        _index[name] = timer;
    }
    // unlock the container
    pthread_mutex_unlock(&_indexLock);
    // and return a reference the timer
    return *timer;
}

// destructor
Display::~Display() {}

// end of file
