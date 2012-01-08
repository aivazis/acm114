#!/usr/bin/env python3.2
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


"""
Grant access to the acm114 homework repositories
"""


# main
if __name__ == "__main__":
    # externals
    import sys
    import syllabus
    # build the app
    app = syllabus.homework(globalAliases=True)
    # invoke it
    status = app.main()
    # pass the status along
    sys.exit(status)
    

# end of file 
