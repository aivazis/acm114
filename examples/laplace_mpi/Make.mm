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
PROJ_TIDY += *.csv *.dSYM
PROJ_CLEAN += $(PROGRAMS) $(PROJ_DLL) $(PROJ_SAR)
PROJ_CXX_FLAGS = -pthread


PROJ_SRCS = \
    Grid.cc \
    Example.cc \
    Jacobi.cc \
    Problem.cc \
    Solver.cc \
    Visualizer.cc \

PROGRAMS = laplace_mpi

#--------------------------------------------------------------------------
#

all: $(PROGRAMS)

#--------------------------------------------------------------------------
#

LIBRARIES = $(PROJ_SAR) $(EXTERNAL_LIBS)

laplace_mpi: laplace_mpi.cc $(PROJ_SAR)
	$(CXX) $(CXXFLAGS) -pthread $< -o $@ $(LCXX_FLAGS) $(LIBRARIES)

# end of file 
