# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


import random
from PointCloud import PointCloud

class Mersenne(PointCloud):
    """
    A point generator implemented using the Mersenne Twister random number
    generator that is available as part of the python standard library
    """

    # interface
    def points(self, n, box):
        """
        Generate {n} random points in the interior of {box}
        """
        # unfold the bounding box
        intervals = tuple(zip(*box))
        # create the container for the sample
        sample = []
        # loop over the sample size
        while n > 0:
            p = [ random.uniform(left, right) for left,right in intervals ]
            sample.append(p)
            n -= 1
        # return the samples
        return sample

# end of file 
