#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


"""
Instantiate a {bzr} server configured to run on a macports based host
"""


def test():
    # get the package
    import syllabus
    # build the instance
    bzr = syllabus.bzr(name='bzr-macports')
    # verify the server command line 
    assert bzr.command == [
        '/opt/local/bin/bzr',
        'serve',
        '--inet',
        '--directory=/tmp',
        '--allow-writes',
        ]
    # return the server
    return bzr


# main
if __name__ == "__main__":
    # do...
    test()


# end of file 
