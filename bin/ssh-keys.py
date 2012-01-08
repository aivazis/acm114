#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#

# externals
import os


# the file writer
def grant_access():
    """
    Create the authorized_keys file
    """
    # externals
    import os

    # open the output file
    keys = open("roll.keys", "w")
    # build the command template
    command = (
        'command="/opt/pyre-1.0/bin/homework.py --student={}"' +
        ',no-port-forwarding,no-X11-forwarding,no-agent-forwarding {}'
        )
    # write the keys to the file
    keys.writelines(command.format(student, key) for student, key in build_key())
    # close the file
    keys.close()
    # all done
    return


def build_key():
    """
    Return a student name and a key from the student's public key file
    """
    # assuming this is run from the correct directory
    for filename in os.listdir('.'):
        # separate the name from the extension
        student, ext = os.path.splitext(filename)
        # skip files that are not public keys
        if ext != '.pub': continue
        # read the student's public key file
        for key in open(filename, "r"):
            # build the associated authorization
            n += 1
            yield student, key
    # all done
    return


# main
if __name__ == "__main__":
    grant_access()


# end of file 
