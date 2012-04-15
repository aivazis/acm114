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

FIGURES = \

LISTINGS = \
    listings/pi.py

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
