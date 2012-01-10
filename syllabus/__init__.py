# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#

# application factories
from .Access import Access as access
from .Homework import Homework as homework
from .RepositoryInitializer import RepositoryInitializer as repositoryInitializer


# interface
def identifyMissingRepositories():
    """
    Build a list of students that don't have homework repositories
    """
    # access the app
    from .MissingRepositories import MissingRepositories
    # build one
    app = MissingRepositories(globalAliases=True)
    # all done
    return app.main()


def postHomeworkAssignment():
    """
    Populate the student homework repositories with a new assignment
    """
    # access the app
    from .PostAssignment import PostAssignment
    # build one
    app = PostAssignment(globalAliases=True)
    # all done
    return app.main()


# component factories
from .ACM114 import ACM114 as acm114
from .Bazaar import Bazaar as bzr



# end of file 
