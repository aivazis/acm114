# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


from Functor import Functor

class Constant(Functor):
    """
    A representation of constant functions
    """

    # interface
    def eval(self, points):
        """
        Compute the value of the function
        """
        # cache the constant
        constant = self.constant
        # return the constant regardless of the evaluation point
        for point in points: yield constant
        # all done
        return

    # meta methods
    def __init__(self, constant):
        self.constant = constant
        return


# end of file 
