#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                             michael a.g. aïvázis
#                      california institute of technology
#                      (c) 1998-2010  all rights reserved
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#

from math import log, log1p, pi as π

# known values of the dilogarithm
identities = {
    -1: -π**2/12,
    1: π**2/6,
     }

# the integral
def dilog(z, n):
    # catch some obvious cases
    if n == 0:
        raise ValueError("number of subdivisions must be positive")
    if z > 1:
        raise ValueError("math domain error")
    if z == 0:
        return 0

    # partition the interval
    dx = z/n
    # compute the first interval center
    x = dx/2
    # initialize the answer
    dilog = 0
    # accumulate the contributions
    for i in range(n):
        dilog += dx * log(1-x)/x
        x += dx
    # all done
    return -dilog

# the driver
if __name__ == "__main__":
    z = 1
    goal = identities[z]
    print("Li2({0}) = {1}".format(z, goal))

    N = 10**7 
    li2 = dilog(z, N)
    print("dilog({0},{1}) = {2},   error={3}".format(z, N, li2, abs(li2-goal)/goal))

# end of file 
