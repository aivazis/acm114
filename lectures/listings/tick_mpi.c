/* -*- coding: utf-8 -*-
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *                             michael a.g. aïvázis
 *                      california institute of technology
 *                      (c) 1998-2010  all rights reserved
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, status;
    
    /* initialize MPI */
    status = MPI_Init(&argc, &argv);
    if (status != MPI_SUCCESS) {
        printf("error in MPI_Init; aborting...\n");
        return status;
    }

    /* all good */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("%03d: dt=%g\n", rank, MPI_Wtick());

    /* shut down MPI */
    MPI_Finalize();
    
    return 0;
}

/* end of file */
