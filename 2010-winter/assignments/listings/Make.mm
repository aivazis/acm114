# -*- Makefile -*-
# -*- coding: utf-8 -*-
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                             michael a.g. aïvázis
#                      california institute of technology
#                      (c) 1998-2010  all rights reserved
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#

PROJECT = acm114

ASSIGNMENTS = \
    dilog_sequential \
    dilog_threads \
    dilog_mpi \
    dilog_cuda \

PROJ_CLEAN += $(ASSIGNMENTS)

#--------------------------------------------------------------------------
#

all: $(ASSIGNMENTS)

#--------------------------------------------------------------------------
#
dilog_sequential: dilog_sequential.cc
	$(CXX) $^ -o $@

dilog_threads: dilog_threads.cc
	$(CXX) -pthread $^ -o $@

dilog_mpi: dilog_mpi.cc
	$(CXX) $^ -o $@ -lmpi_cxx -lmpi

dilog_cuda: dilog_cuda.cu
	nvcc $^ -o $@

test:
	dilog_threads -N 8
	dilog_threads -N 64
	dilog_threads -N 512
	dilog_threads -N 4096
	dilog_threads -N 32768
	dilog_threads -N 262144

# end of file 
