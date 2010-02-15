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
#include <assert.h>
#include <iostream>
#include "BCD.h"

using namespace pyre::timers;

// main program
int main(int argc, char* argv[]) {

    BCD<10> a;
    BCD<10> b(0,1);
    BCD<10> c(0,9);
    BCD<10> d(1,1);
    BCD<10> e(1,9);

    assert(a == 0.0);
    assert(b+c == 1.0);
    assert(b+d == 1.2);
    assert(c+d == 2.0);
    assert(c+e == 2.8);
    assert(d+e == 3.0);

    return 0;
}

// end of file
