#!/usr/bin/env python3.2
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


# externals
import os
import pyre
import subprocess


# declaration
class RepositoryInitializer(pyre.application):
    """
    Initialize the bzr repositories with the students' homework
    """

    # types
    from .interfaces import Course, Repository
    

    # public state
    course = pyre.facility(interface=Course)
    course.doc = 'the course whose students are granted access'

    repository = pyre.facility(interface=Repository)
    repository.doc = 'the repository server'


    # interface
    @pyre.export
    def main(self, *args, **kwds):
        """
        Initialize the student homework repositories
        """
        # get the path to the student roll
        roll = self.course.roll()
        # get the path to the student homework repositories
        homework = self.course.homework()

        # each file corresponds to a student
        for filename in os.listdir(roll):
            # separate the name from the extension
            student, ext = os.path.splitext(filename)
            # skip files that are not public keys
            if ext != '.pub': continue
            
            # build the absolute path to repository
            repo = os.path.abspath(os.path.join(homework, student))
            # if the directory exists and it is a directory, skip it
            if os.path.isdir(repo): continue
            # get the server to initialize this repository
            self.repository.initialize(repo)

        # all done
        return 0


    # meta methods
    def __init__(self, name='init-repo', **kwds):
        super().__init__(name=name, **kwds)
        return


# end of file 
