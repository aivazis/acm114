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
import pyre


# declaration
class Homework(pyre.application):
    """
    Grant repository access to the student's homework repositories
    """

    # types
    from .interfaces import Course, Repository
    

    # public state
    course = pyre.facility(interface=Course)
    course.doc = 'the course whose materials are being served'

    student = pyre.properties.str()
    student.doc = 'the name of the student whose homework is being served'

    repository = pyre.facility(interface=Repository)
    repository.doc = 'the repository server'


    # interface
    @pyre.export
    def main(self, *args, **kwds):
        """
        Serve the contents of some student's homework repository
        """
        # get the path to the homework
        path = self.course.homework(student=self.student)
        # use it as the root for the repository
        self.repository.root = path
        # and the repository to serve its contents
        return self.repository.serve()


    # meta methods
    def __init__(self, name='homework', **kwds):
        super().__init__(name=name, **kwds)
        return


# end of file 
