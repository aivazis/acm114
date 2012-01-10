#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


"""
Build the authorized_keys file that grants limited access to the course directories
"""


# main
if __name__ == "__main__":
    # externals
    import sys
    import syllabus
    # post the assignment
    status = syllabus.postHomeworkAssignment()
    # and pass the status back to the shell
    sys.exit(status)


# end of file 
