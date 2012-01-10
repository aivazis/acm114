#!/usr/bin/env python3.2
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


"""
Post an assignment to the student homework repositories
"""

# externals
import os
import pyre


# declaration
class MissingRepositories(pyre.application):
    """
    Identify the students with no homework repository
    """

    # types
    from .interfaces import Course
    

    # public state
    course = pyre.facility(interface=Course)
    course.doc = 'the course whose materials are being served'


    # interface
    @pyre.export
    def main(self, *args, **kwds):
        """
        Post the assignment
        """
        # locate the enrolled students
        enrolled = set(self.roll())
        # locate the ones that have homework repositories
        repos = set(self.repositories())
        # compute the difference
        missing = enrolled - repos
        # print it is a comma separated list
        print(','.join(missing))
        # all done
        return 0


    # meta methods
    def __init__(self, name='hw-missing', **kwds):
        super().__init__(name=name, **kwds)
        return


    # implementation details
    def repositories(self):
        """
        Generate the list of enrolled students
        """
        # otherwise, get the path to the student roll
        homework = self.course.homework()
        # each directory corresponds to a student
        for student in os.listdir(homework):
            # form the repository path
            repo = os.path.abspath(os.path.join(homework, student))
            # if it's not a directory, skip it
            if not os.path.isdir(repo): continue
            # yield the student name
            yield student
        # all done
        return


    def roll(self):
        """
        Generate the list of enrolled students
        """
        # otherwise, get the path to the student roll
        roll = self.course.roll()
        # each file corresponds to a student
        for filename in os.listdir(roll):
            # separate the name from the extension
            student, ext = os.path.splitext(filename)
            # skip files that are not public keys
            if ext != '.pub': continue
            # yield the student name
            yield student
        # all done
        return


# end of file 
