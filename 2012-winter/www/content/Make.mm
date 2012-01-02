# -*- Makefile -*-
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                             michael a.g. aïvázis
#                      california institute of technology
#                      (c) 1998-2012  all rights reserved
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#


PROJECT = acm114
PACKAGE = www/2012-winter/content


#--------------------------------------------------------------------------
#

all: tidy

export::
	/usr/bin/rsync --delete -ruavz . acm114@pyre.caltech.edu:web/$(PACKAGE)

# end of file 
