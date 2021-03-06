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
PACKAGE = 2010-winter/www
WEB = acm114@pyre.caltech.edu:web/$(PACKAGE)

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
	/usr/bin/rsync --delete -ruavz . $(WEB)

try-export:
	/usr/bin/rsync -n --delete -ruavz . $(WEB)

# end of file 
