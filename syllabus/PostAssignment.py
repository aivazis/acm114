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
import shutil
import subprocess


# declaration
class PostAssignment(pyre.application):
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

    assignment = pyre.properties.str()
    assignment.doc = 'the name of the assignment'

    due = pyre.properties.str()
    due.doc = 'the due date of the assignment'


    # interface
    @pyre.export
    def main(self, *args, **kwds):
        """
        Post the assignment
        """
        # locate the assignment pdf file
        pdf = os.path.join(
            self.course.webContent(),
            '{}-hw-{}.pdf'.format(self.course.name, self.due))
        print("pdf: {!r}".format(pdf))

        # locate the source of the assignment
        assignmentSource = self.course.assignmentSource(assignment=self.assignment)
        print("assignment source: {!r}".format(assignmentSource))

        # iterate over the selected students
        for student in self.selectedStudents():
            # get the root of the student homework repository
            root = self.course.homework(student)
            print(" -- posting at {!r}".format(root))
            # if the repository doesn't exist
            if not os.path.isdir(root):
                # initialize it
                self.repository.initialize(root)

            # bring the tree up to date
            self.repository.update(root)

            # construct the name of the assignment directory
            directory = os.path.join(root, 'assignment-{}'.format(self.assignment))
            # if it doesn't exist
            if not os.path.isdir(directory):
                # create it
                os.mkdir(directory)

            # copy the assignment pdf here
            shutil.copy2(pdf, directory)
            # copy the sources
            for name in os.listdir(assignmentSource):
                # form the absolute path to the source file
                srcName = os.path.join(assignmentSource, name)
                # and the absolute path to the destination
                dstName = os.path.join(directory, name)
                # if the source is a directory
                if os.path.isdir(srcName):
                    # copy its entire contents
                    shutil.copytree(srcName, dstName)
                # otherwise
                else:
                    # copy the file over
                    shutil.copy2(srcName, dstName)

            # ask the server to add this directory to the repository
            self.repository.add(directory)
            # and to commit it
            self.repository.commit(
                path=directory,
                message='posted assignment {}'.format(self.assignment))

            print(" -- done posting at {!r}".format(root))

        return 0


    # meta methods
    def __init__(self, name='hw-post', **kwds):
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
