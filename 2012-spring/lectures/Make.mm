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

FIGURES = \
    figures/gauss-namespace.pdf \

LISTINGS = \
    listings/simple/pi.py \
    listings/simple/pi.cc \
    listings/simple/PointCloud.py \
    listings/simple/Mersenne.py \
    listings/simple/Shape.py \
    listings/simple/Disk.py \
    listings/containers/gauss.py \
    listings/containers/PointCloud.py \
    listings/containers/Mersenne.py \
    listings/containers/Shape.py \
    listings/containers/Disk.py \
    listings/generators/gauss.py \
    listings/generators/gauss-mc.py \
    listings/generators/PointCloud.py \
    listings/generators/Mersenne.py \
    listings/generators/Shape.py \
    listings/generators/Disk.py \
    listings/generators/Functor.py \
    listings/generators/Constant.py \
    listings/generators/Gaussian.py \

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
