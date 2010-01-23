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

#--------------------------------------------------------------------------
#
dilog: dilog.cc
	$(CXX) $< -o $@

hello_threads: hello_threads.cc
	$(CXX) -pthread $< -o $@

hello_mpi: hello_mpi.c
	$(CC) $< -o $@ -lmpi

squares_threads: squares_threads.c
	$(CXX) -pthread $< -o $@

squares_mpi: squares_mpi.c
	$(CC) $< -o $@ -lmpi


PROJ_CLEAN += dilog *_threads *_mpi


# end of file 
