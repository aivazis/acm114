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
PACKAGE = 2010-winter/www/sctyles
WEB = acm114@pyre.caltech.edu:web/$(PACKAGE)


#--------------------------------------------------------------------------
#

all: tidy

export::
	/usr/bin/rsync --delete -ruavz . $(WEB)

# end of file 
