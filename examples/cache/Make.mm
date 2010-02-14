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
PACKAGE = libcache

PROJ_SAR = $(BLD_LIBDIR)/$(PACKAGE).$(EXT_SAR)
PROJ_DLL = $(BLD_LIBDIR)/$(PACKAGE).$(EXT_SO)
PROJ_TMPDIR = $(BLD_TMPDIR)/$(PROJECT)/$(PACKAGE)
PROJ_TIDY += *.csv *.dSYM
PROJ_CLEAN += $(PROGRAMS) $(PROJ_DLL) $(PROJ_SAR)
PROJ_CXX_FLAGS = -pthread

RECURSE_DIRS = \
    darwin

PROJ_SRCS = \
    Display.cc \
    Timer.cc \


PROJ_TEMPLATES = \
    Display.h Display.icc \
    Registrar.h Registrar.icc \
    Timer.h Timer.icc\

PROGRAMS = abi cache

#--------------------------------------------------------------------------
#

all: $(PROGRAMS)

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

distclean::
	BLD_ACTION="distclean" $(MM) recurse


#--------------------------------------------------------------------------
#

LIBRARIES = $(PROJ_SAR) $(EXTERNAL_LIBS)

abi: abi.cc
	$(CXX) $(CXXFLAGS) $< -o $@ $(LCXX_FLAGS)

cache: cache.cc $(PROJ_TEMPLATES) $(PROJ_SAR)
	$(CXX) -O4 $(CXXFLAGS) -pthread $< -o $@ $(LCXX_FLAGS) $(LIBRARIES)

# end of file 
