# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


class Shape(object):
    """
    The abstract base class for representations of geometrical regions
    """

    # interface
    def interior(self, points):
        """
        Examine each point in {points} and return a container of only the
        interior points
        """
        raise NotImplementedError(
            "class {.__name__!r} should implement 'interior'".format(type(self)))


# end of file 
