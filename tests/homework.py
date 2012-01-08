#!/usr/bin/env python3.2
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


"""
Grant access to the acm114 repositories
"""

# externals
import syllabus


def test():
    # build the app
    app = syllabus.homework()

    # check that it is properly configured
    # the course
    course = app.course
    assert course.name == 'acm114'
    assert course.home == '/home/projects/acm114/web'
    assert course.term == '2012-winter'
    # the repository
    repository = app.repository
    assert repository.pyre_name == 'bzr-ubuntu'
    assert repository.executable == '/usr/bin/bzr'

    # return the application object
    return app


# main
if __name__ == "__main__":
    # do...
    test()


# end of file 
