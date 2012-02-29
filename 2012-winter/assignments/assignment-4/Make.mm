# -*- Makefile -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#

PROJECT = acm114
PACKAGE = assignments
DOCUMENT = 20120316

all: $(DOCUMENT).pdf

export:: $(DOCUMENT).pdf
	mv $(DOCUMENT).pdf ../../www/content/acm114-hw-$(DOCUMENT).pdf

# preview types
osx: $(DOCUMENT).pdf
	open -g $(DOCUMENT).pdf

xpdf: $(DOCUMENT).pdf
	xpdf -remote $(DOCUMENT) $(DOCUMENT).pdf

# make a document
%.pdf: %.tex


# housekeeping
PROJ_CLEAN += $(CLEAN_LATEX) *.snm *.nav *.vrb 
PROJ_DISTCLEAN += *.ps $(PROJ_CLEAN)

# end of file
