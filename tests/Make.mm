# -*- Makefile -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


PROJECT = syllabus
PROJ_CLEAN += __pycache__

#--------------------------------------------------------------------------
#

all: test

test: sanity servers course

sanity:
	${PYTHON} ./sanity.py
	${PYTHON} ./bzr.py
	${PYTHON} ./course.py

servers:
	${PYTHON} ./bzr_macports.py --config=test.pml
	${PYTHON} ./bzr_macports_invoke.py --config=test.pml
	${PYTHON} ./bzr_ubuntu.py --config=test.pml
	${PYTHON} ./bzr_ubuntu_invoke.py --config=test.pml

course:
	${PYTHON} ./course_instantiation.py --config=test.pml
	${PYTHON} ./homework.py --config=test.pml


# end of file 
