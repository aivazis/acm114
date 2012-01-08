# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


# externals
import os
import pyre
# interfaces
from .interfaces import Repository as repository


class ACM114(pyre.component, family='syllabus.courses.acm114'):
    """
    The ACM114 course material manager
    """

    # public data
    name = 'acm114'


    # public state
    home = pyre.properties.str(default='/home/projects/acm114/web')
    home.doc = 'root of the course directory structure'

    term = pyre.properties.str(default='2012-winter')
    term.doc = 'the course term'


    # interface
    @pyre.export
    def homework(self, student=None):
        """
        Return the location of the {student}'s homework directory
        """
        # build the path
        path = os.path.join(*filter(None, (self.home, self.term, 'homework', student)))
        # and return it
        return path


    # meta methods
    def __init__(self, name='acm114', **kwds):
        super().__init__(name=name, **kwds)
        return


# end of file 
