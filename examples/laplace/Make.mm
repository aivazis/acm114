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
PACKAGE = liblaplace

PROJ_SAR = $(BLD_LIBDIR)/$(PACKAGE).$(EXT_SAR)
PROJ_DLL = $(BLD_LIBDIR)/$(PACKAGE).$(EXT_SO)
PROJ_TMPDIR = $(BLD_TMPDIR)/$(PROJECT)/$(PACKAGE)
PROJ_CLEAN += laplace *.csv *.dSYM $(PROJ_DLL) $(PROJ_SAR)

PROJ_SRCS = \
    Example.cc \
    Grid.cc \
    Problem.cc \


#--------------------------------------------------------------------------
#

all: laplace

#--------------------------------------------------------------------------
#

laplace: laplace.cc $(PROJ_SAR)
	$(CXX) -pthread -g -o $@ $^

# end of file 
