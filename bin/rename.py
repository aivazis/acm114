#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


def rename():
    """
    Replace '.' with '-' as the separator between first and last names in the students' public
    key files
    """
    # externals
    import os
    import subprocess

    # assuming this is run from the correct directory
    for old in os.listdir('.'):
        # separate the name from the extension
        name, ext = os.path.splitext(old)
        # skip files that are not public keys
        if ext != '.pub': continue
        # replace '.' with '-'
        name = '-'.join(name.split('.'))
        # reassemble the name
        new = name+ext
        # build the command line for bzr
        command = ['bzr', 'mv', old, new]
        # and invoke it
        subprocess.call(command)
    # all done
    return


# main
if __name__ == "__main__":
    rename()

# end of file 
