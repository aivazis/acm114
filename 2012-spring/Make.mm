# -*- Makefile -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


PROJECT = acm114
PACKAGE = 2012-spring

RECURSE_DIRS = \
    roll \
    lectures \
    www \

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
