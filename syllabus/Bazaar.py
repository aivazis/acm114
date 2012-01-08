# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#


# externals
import pyre
import subprocess
# my interface
from .interfaces import Repository as repository


# declaration
class Bazaar(pyre.component, family="syllabus.repositories.bzr", implements=repository):
    """
    Encapsulation of a {bzr} server running on the repository host.

    {Bazaar} instances restrict filesystem access to subdirectories of {root}, and control
    whether the client is granted write privileges to the repository.
    """


    # public state
    executable = pyre.properties.str(default='/usr/bin/bzr')
    executable.doc = 'the path to the server executable'

    root = pyre.properties.str(default='/tmp')
    root.doc = 'the top level directory to which access is granted'

    write = pyre.properties.bool(default=True)
    write.doc = 'control whether the client has write permissions to the repository'
    

    # interface
    @property
    def command(self):
        """
        Assemble the parts of the server command line
        """
        # build the command line
        commands = [
            self.executable,
            'serve',
            '--inet',
            '--directory={}'.format(self.root)
            ]
        # should we grant write access?
        if self.write: commands.append('--allow-writes')
        # return it
        return commands


    @pyre.export
    def serve(self):
        """
        Invoke the repository server to satisfy the client request
        """
        # invoke the server
        return subprocess.call(self.command)
    

# end of file 