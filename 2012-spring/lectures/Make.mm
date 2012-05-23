# -*- Makefile -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
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
    acm114.sty \
    setup.tex \
    references.bib

SECTIONS = \
    20120404.tex \
    20120406.tex \
    20120409.tex \
    20120411.tex \
    20120413.tex \
    20120416.tex \
    20120418.tex \
    20120507.tex \
    20120509.tex \
    20120511.tex \
    20120514.tex \
    20120516.tex \
    20120518.tex \
    20120523.tex \
    20120525.tex \

FIGURES = \
    figures/gauss-namespace.pdf \

LISTINGS = \
    listings/simple/*.py \
    listings/simple/*.cc \
    listings/containers/*.py \
    listings/generators/*.py \
    listings/gauss/*.py \
    listings/gauss/functors/*.py \
    listings/gauss/integrators/*.py \
    listings/gauss/meshes/*.py \
    listings/gauss/shapes/*.py \

#--------------------------------------------------------------------------
#

all: $(DOCUMENT).pdf

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
	open -g $(DOCUMENT).pdf

xpdf: $(DOCUMENT).pdf
	xpdf -remote $(DOCUMENT) $(DOCUMENT).pdf

# make the document using the default document class
$(DOCUMENT).pdf: $(DOCUMENT).tex $(PACKAGES) $(INCLUDES) $(SECTIONS) $(FIGURES) $(LISTINGS)

# housekeeping
PROJ_CLEAN += $(CLEAN_LATEX) *.snm *.nav *.vrb 
PROJ_DISTCLEAN += *.ps *.pdf $(PROJ_CLEAN)

# end of file
