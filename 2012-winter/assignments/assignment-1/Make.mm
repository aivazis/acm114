# -*- Makefile -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#

PROJECT = acm114
PACKAGE = lectures

#--------------------------------------------------------------------------
#

DOCUMENT = 20120120

#--------------------------------------------------------------------------
#

all: $(DOCUMENT).pdf


#--------------------------------------------------------------------------
#

# preview types
osx: $(DOCUMENT).pdf
	open -g $(DOCUMENT).pdf

xpdf: $(DOCUMENT).pdf
	xpdf -remote $(DOCUMENT) $(DOCUMENT).pdf

# make a document
%.pdf: %.tex


# housekeeping
PROJ_CLEAN += $(CLEAN_LATEX) *.snm *.nav *.vrb 
PROJ_DISTCLEAN += *.ps *.pdf $(PROJ_CLEAN)


# end of file