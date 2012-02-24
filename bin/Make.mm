# -*- Makefile -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


PROJECT = acm114
PACKAGE = bin


#--------------------------------------------------------------------------
#

all: export

#--------------------------------------------------------------------------
# export

EXPORT_BINS = \
    homework.py \
    hw-missing.py \
    hw-post.py \
    hw-init-repos.py \
    project-init.py \
    ssh-keys.py \

export:: export-binaries


# end of file 
