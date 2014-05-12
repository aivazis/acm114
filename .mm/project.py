# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2011 all rights reserved
#


def requirements(package):
    """
    Build a dictionary with the external dependencies of the {pyre} project
    """

    # build the package instances
    packages = (
        package(name='gsl', optional=False),
        package(name='mpi', optional=True),
        package(name='python', optional=False),
        )
    # attach
    return { package.name: package for package in packages }


# end of file 
