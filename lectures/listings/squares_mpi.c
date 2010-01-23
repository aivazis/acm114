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
    int status;
    int rank;
    int square, sum;

    /* initialize MPI */
    status = MPI_Init(&argc, &argv);
    if (status != MPI_SUCCESS) {
        printf("error in MPI_Init; aborting...\n");
        return status;
    }

    /* get the process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    /* form the square */
    square = rank*rank;
    /* each process contributes the square of its rank */
    MPI_Allreduce(&square, &sum, 1, MPI_INT,  MPI_SUM, MPI_COMM_WORLD);
    /* print out the result */
    printf("%03d: sum = %d\n", rank, sum);

    /* shut down MPI */
    MPI_Finalize();

    return 0;
}
/* end of file */
