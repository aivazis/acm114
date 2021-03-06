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


#--------------------------------------------------------------------------
#

all: tidy

TESTS = \
    abi \
    dilog \
    hello_threads \
    hello_mpi \
    laplace \
    squares_threads \
    squares_mpi \
    tick_mpi \
    memxchng_cuda \
    scale_cuda \

#--------------------------------------------------------------------------
#
abi: abi.cc
	$(CXX) $< -o $@

dilog: dilog.cc
	$(CXX) $< -o $@

hello_threads: hello_threads.cc
	$(CXX) -pthread $< -o $@

hello_mpi: hello_mpi.c
	$(CC) $< -o $@ -lmpi

laplace: laplace.cc
	$(CXX) -g $< -o $@

squares_threads: squares_threads.c
	$(CXX) -pthread $< -o $@

squares_mpi: squares_mpi.c
	$(CC) $< -o $@ -lmpi

tick_mpi: tick_mpi.c
	$(CC) $< -o $@ -lmpi

memxchng_cuda: memxchng.cu
	nvcc $< -o $@

scale_cuda: scale.cu
	nvcc $< -o $@

PROJ_CLEAN += ${TESTS} *.csv *.dSYM


# end of file 
