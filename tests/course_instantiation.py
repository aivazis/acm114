#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


"""
Instantiate the course master object
"""


def test():
    # access the package
    import syllabus
    # build the master course object
    course = syllabus.acm114(name='acm114')
    # check for errors
    errors = course.pyre_executive.errors
    for error in errors: print(error)
    assert not course.pyre_executive.errors

    # check the simple properties
    assert course.term == '2012-winter'
    assert course.home == '/home/projects/acm114/web'
    assert course.homework() == '/home/projects/acm114/web/2012-winter/homework'
    assert course.homework(student='test') == '/home/projects/acm114/web/2012-winter/homework/test'

    # and return it
    return course


# main
if __name__ == "__main__":
    # do...
    test()


# end of file 
