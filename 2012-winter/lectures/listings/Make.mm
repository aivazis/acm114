# -*- Makefile -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#

PROJECT = acm114
PROJ_CLEAN += ${TESTS} *.csv *.dSYM

TESTS = \
    dilog-sequential \
    dilog-threads \
    dilog-mpi \

#--------------------------------------------------------------------------

all: ${TESTS}

#--------------------------------------------------------------------------

dilog-sequential: dilog-sequential.cc
	$(CXX) $< -o $@

dilog-threads: dilog-threads.cc
	$(CXX) -pthread $< -o $@

dilog-mpi: dilog-mpi.cc
	$(CXX) $(CXXFLAGS) $< -o $@ $(LCXXFLAGS) $(EXTERNAL_LIBS)

# end of file 
