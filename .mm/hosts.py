# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2011 all rights reserved
#

# externals
import os


# the builder decorator
def host(builder):
    """
    Decorate the {builder} with host specific options
    """
    # get the host name
    name = builder.host.name
    # print('host:', name)

    # on shc.cacr.caltech.edu
    if name.startswith('shc'):
        systemdir = '/usr'
        # set up {gsl}
        gslHome = os.environ['GSL_HOME']
        builder.requirements['gsl'].environ = {
            'GSL_DIR': gslHome,
            'GSL_LIBDIR': os.path.join(gslHome, 'lib'),
            'GSL_INCDIR': os.path.join(gslHome, 'include'),
            }
        # set up {mpi}
        mpiVersion = 'openmpi'
        mpiHome = os.environ['OPENMPI_HOME']
        builder.requirements['mpi'].environ = {
            'MPI_VERSION': mpiVersion,
            'MPI_DIR': mpiHome,
            'MPI_BINDIR': os.path.join(mpiHome, 'bin'),
            'MPI_LIBDIR': os.path.join(mpiHome, 'lib'),
            'MPI_INCDIR': os.path.join(mpiHome, 'include'),
            'MPI_EXECUTIVE': 'mpirun',
            }
        # set up {python}
        pythonVersion = '3.2'
        python = 'python' + pythonVersion
        pythonHome = '/usr/local/python-3.2.2'
        builder.requirements['python'].environ = {
            'PYTHON': python,
            'PYTHON_PYCFLAGS': '-b',
            'PYTHON_DIR': pythonHome,
            # 'PYTHON_LIBDIR': os.path.join(pythonHome, 'lib', python),
            'PYTHON_INCDIR': os.path.join(pythonHome, 'include', python+'m'),
            }
        # all done
        return builder
        
    # for all other hosts
    return builder


# end of file 
