# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


from Shape import Shape

class Disk(Shape):
    """
    A representation of a circular disk
    """

    # interface
    def interior(self, points):
        """
        Predicate that filters out points that are not in my interior
        """
        # precompute the frequently used values
        r2 = self.radius**2
        x0, y0 = self.center
        # iterate over the given points and return the interior ones
        for point in points:
            x, y = point
            dx = x - x0
            dy = y - y0
            if dx*dx + dy*dy <= r2:
                yield point
        # all done
        return


    # meta methods
    def __init__(self, radius=1.0, center=(0.0, 0.0)):
        self.radius = radius
        self.center = center
        return


# end of file 
