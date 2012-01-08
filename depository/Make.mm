# -*- Makefile -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


PROJECT = sullabus
PACKAGE = depository

#--------------------------------------------------------------------------
#

all: export


#--------------------------------------------------------------------------
#

EXPORT_ETCDIR = $(EXPORT_ROOT)
EXPORT_ETC = \
    syllabus.pml \


export:: export-etc


# end of file 
