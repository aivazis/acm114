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

#if !defined(acm114_laplace_Visualizer_h)
#define acm114_laplace_Visualizer_h

#include <ostream>

namespace acm114 {
    namespace laplace {
        class Problem;
        class Visualizer;
    }
}


// the visualizer class
class acm114::laplace::Visualizer {

    // local type aliases
public:
    typedef std::ostream stream_t;

    // interface
public:
    void csv(const Problem & problem);

    // meta methods
public:
    inline Visualizer() {}
};

#endif

// end of file
