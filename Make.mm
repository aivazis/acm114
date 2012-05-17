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
PACKAGE = 

RECURSE_DIRS = \
    syllabus \
    depository \
    bin \
    tests \
    2010-winter \
    2012-winter \
    2012-spring \
    examples \
    templates \

#--------------------------------------------------------------------------
#

tools:
	@(cd syllabus; $(MM) export)
	@(cd depository; $(MM) export)
	@(cd bin; $(MM) export)

#--------------------------------------------------------------------------
#

all: tidy export

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

distclean::
	BLD_ACTION="distclean" $(MM) recurse

export::
	BLD_ACTION="export" $(MM) recurse


# end of file 
