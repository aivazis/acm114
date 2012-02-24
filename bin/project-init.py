#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


"""
Post a homework assignment to the students' homework repositories
"""


# main
if __name__ == "__main__":
    # externals
    import sys
    import syllabus
    # post the assignment
    status = syllabus.createProjectDirectory()
    # and pass the status back to the shell
    sys.exit(status)


# end of file 
