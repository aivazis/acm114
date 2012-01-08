# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


# externals
import pyre


# repositories
class Repository(pyre.interface, family='syllabus.repositories'):
    """
    Encapsulation of a repository server running on the repository host.

    {Repository} instances restrict filesystem access to subdirectories of {root}, and control
    whether the client is granted write privileges to the repository.
    """

    # public state
    root = pyre.properties.str(default='/tmp')
    root.doc = 'the top level directory to which access is granted'

    write = pyre.properties.bool(default=True)
    write.doc = 'control whether the client has write permissions to the repository'

    # the default implementation
    @classmethod
    def default(cls):
        """
        Use {Bazaar} as the default repository type
        """
        # access the class record
        from .Bazaar import Bazaar
        # and return it
        return Bazaar
    
    # interface
    @pyre.provides
    def serve(self):
        """
        Invoke the repository server to satisfy the client request
        """


# courses
class Course(pyre.interface, family='syllabus.courses'):
    """
    Course interface specification
    """

    # public state
    home = pyre.properties.str()
    home.doc = 'root of the course directory structure'

    term = pyre.properties.str()
    term.doc = 'the course term'

    # interface
    @pyre.provides
    def homework(self, student=None):
        """
        Return the location of the {student}'s homework directory
        """


# users
class User(pyre.interface, family='syllabus.users'):
    """
    Encapsulation of user attributes
    """

    # public state
    name = pyre.properties.str()
    email = pyre.properties.str()


# end of file 
