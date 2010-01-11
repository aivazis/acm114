# -*- Makefile -*-
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
PACKAGE = lectures

RECURSE_DIRS = \
   figures \
   listings \

OTHERS = \

#--------------------------------------------------------------------------
#

DOCUMENT = acm114

PACKAGES =

INCLUDES = \
    beamerthemeacm114.sty \
    setup.tex \
    references.bib

SECTIONS = \
    20100104.tex \
    20100106.tex \
    20100108.tex \
    20100111.tex \
    sandbox.tex \

FIGURES = \
    figures/generic-parallel-architecture.pdf \
    figures/shared-memory.pdf \
    figures/simd.pdf \
    figures/distributed-memory.pdf \
    figures/reduction-shared.pdf \
    figures/reduction-distributed.pdf \
    figures/reduction-simd.pdf \

#--------------------------------------------------------------------------
#

all: $(DOCUMENT).pdf
	BLD_ACTION="all" $(MM) recurse

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

distclean::
	BLD_ACTION="distclean" $(MM) recurse


#--------------------------------------------------------------------------
#

# preview types
osx: $(DOCUMENT).pdf
	open $(DOCUMENT).pdf

xpdf: $(DOCUMENT).pdf
	xpdf -remote $(DOCUMENT) $(DOCUMENT).pdf

# make the document using the default document class
$(DOCUMENT).pdf: $(DOCUMENT).tex $(PACKAGES) $(INCLUDES) $(SECTIONS) $(FIGURES)

# housekeeping
PROJ_CLEAN = $(CLEAN_LATEX) *.snm *.nav *.vrb 
PROJ_DISTCLEAN = *.ps *.pdf $(PROJ_CLEAN)

# end of file
