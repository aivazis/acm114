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
