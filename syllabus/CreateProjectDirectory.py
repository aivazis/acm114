#!/usr/bin/env python3.2
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


"""
Create the project folder
"""

# externals
import os
import pyre
import shutil
import subprocess


# declaration
class CreateProjectDirectory(pyre.application):
    """
    Grant repository access to the student's homework repositories
    """

    # types
    from .interfaces import Course, Repository
    

    # public state
    course = pyre.facility(interface=Course)
    course.doc = 'the course whose materials are being served'

    repository = pyre.facility(interface=Repository)
    repository.doc = 'the repository server'

    students = pyre.properties.tuple()
    students.doc = 'the names of the students whose repository is being modified'

    dry = pyre.properties.bool(default=False)
    dry.doc = 'dry run'

    # interface
    @pyre.export
    def main(self, *args, **kwds):
        """
        Create the project directory
        """
        # print out the state
        print(' * {.pyre_name}:'.format(self))
        print('     students: {}'.format(self.students))
        print('     repository: {}'.format(self.repository.pyre_name))
        print('         family: {}'.format(self.repository.pyre_getFamilyName()))
        print('         executable: {}'.format(self.repository.executable))
        print('         root: {}'.format(self.repository.root))
        print('     course: {}'.format(self.course.pyre_name))
        print('         family: {}'.format(self.course.pyre_getFamilyName()))
        print('         term: {}'.format(self.course.term))
        print('         home: {}'.format(self.course.home))
        print('         source: {}'.format(self.course.source))

        if self.dry: return

        # iterate over the selected students
        for student in self.selectedStudents():
            # get the root of the student homework repository
            root = self.course.homework(student)
            print(" -- creating project directory at {!r}".format(root))
            # if the repository doesn't exist
            if not os.path.isdir(root):
                # initialize it
                self.repository.initialize(root)

            # bring the tree up to date
            self.repository.update(root)

            # construct the name of the project directory
            directory = os.path.join(root, 'project')
            # if it doesn't exist
            if not os.path.isdir(directory):
                # create it
                os.mkdir(directory)

            # ask the server to add this directory to the repository
            self.repository.add(directory)
            # and to commit it
            self.repository.commit(
                path=directory, message='created project directory')

            print(" -- done creating project directory at {!r}".format(root))

        return 0


    # meta methods
    def __init__(self, name='project-init', **kwds):
        super().__init__(name=name, **kwds)
        return


    # implementation details
    def selectedStudents(self):
        """
        Generate the list of affected students
        """
        # if we were asked to process all students
        if self.students == ('all',):
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

        # if we were given an explicit list
        if self.students:
            # iterate over it
            for student in self.students: yield student
            # and no more
            return

        # otherwise, do nothing
        return


# end of file 
