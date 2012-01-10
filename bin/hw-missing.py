#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


"""
Identify which students don't have a homework repository
"""


# main
if __name__ == "__main__":
    # externals
    import sys
    import syllabus
    # post the assignment
    status = syllabus.identifyMissingRepositories()
    # and pass the status back to the shell
    sys.exit(status)


# end of file 
