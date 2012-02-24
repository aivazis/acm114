# -*- Makefile -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


PROJECT = syllabus
PACKAGE = syllabus
PROJ_DISTCLEAN = $(EXPORT_MODULEDIR)


#--------------------------------------------------------------------------
#

all: export

#--------------------------------------------------------------------------
# export

EXPORT_PYTHON_MODULES = \
    ACM114.py \
    Access.py \
    Bazaar.py \
    CreateProjectDirectory.py \
    Homework.py \
    MissingRepositories.py \
    PostAssignment.py \
    RepositoryInitializer.py \
    interfaces.py \
    __init__.py


export:: export-python-modules

# end of file 
