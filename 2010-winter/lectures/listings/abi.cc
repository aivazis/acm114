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
#include <iostream>

// main program
int main(int argc, char* argv[]) {

    std::cout
        << " builtin types:" << std::endl
        << "        sizeof(char): " << sizeof(char) << std::endl
        << "         sizeof(int): " << sizeof(int) << std::endl
        << "        sizeof(long): " << sizeof(long) << std::endl
        << "      sizeof(void *): " << sizeof(void *) << std::endl
        << "   sizeof(long long): " << sizeof(long long) << std::endl
        << "      sizeof(double): " << sizeof(double) << std::endl
        << std::endl
        << " typedefs:" << std::endl
        << "     sizeof(wchar_t): " << sizeof(wchar_t) << std::endl
        << "      sizeof(size_t): " << sizeof(size_t) << std::endl
        << std::endl;

    return 0;
}

// end of file
