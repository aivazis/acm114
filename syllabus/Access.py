#!/usr/bin/env python3.2
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


# externals
import os
import pyre


# declaration
class Access(pyre.application):
    """
    Build the authorized_keys file that grants limited access to the course directories
    """

    # types
    from .interfaces import Course
    

    # public state
    course = pyre.facility(interface=Course)
    course.doc = 'the course whose students are granted access'


    # interface
    @pyre.export
    def main(self, *args, **kwds):
        """
        Serve the contents of some student's homework repository
        """
        # open the output file
        keys = open("roll.keys", "w")
        # build the command template
        command = (
            'command="/opt/pyre-1.0/bin/homework.py --student={}"' +
            ',no-port-forwarding,no-X11-forwarding,no-agent-forwarding {}'
            )
        # write the keys to the file
        keys.writelines(command.format(student, key) for student, key in self.buildKey())
        # close the file
        keys.close()
        # all done
        return 0


    # meta methods
    def __init__(self, name='access', **kwds):
        super().__init__(name=name, **kwds)
        return


    # implementation details
    def buildKey(self):
        """
        Return a student name and a key from the student's public key file
        """
        # get the path to the student roll
        roll = self.course.roll()
        # for each file
        for filename in os.listdir(roll):
            # separate the name from the extension
            student, ext = os.path.splitext(filename)
            # skip files that are not public keys
            if ext != '.pub': continue
            # assemble the path to the key file
            keyfile = os.path.abspath(os.path.join(roll, filename))
            # read the student's public key file
            for key in open(keyfile, "r"):
                # build the associated authorization
                yield student, key
        # all done
        return


# end of file 
