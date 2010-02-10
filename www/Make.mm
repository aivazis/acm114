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
PACKAGE = www

RECURSE_DIRS = \
    content \
    images \
    scripts \
    styles \


#--------------------------------------------------------------------------
#

all: tidy 

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

distclean::
	BLD_ACTION="distclean" $(MM) recurse

export::
	/usr/bin/rsync --delete -ruavz . acm114@pyre.caltech.edu:web/www

try-export:
	/usr/bin/rsync -n --delete -ruavz . acm114@pyre.caltech.edu:web/www

# end of file 
