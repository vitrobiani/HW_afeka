
#include "/home/vitrobiani/.nix-profile/include/mpi.h"
#include <stdio.h>

/*
 * calculates the time it takes for a message to get from one process to another
 */
int main(int argc, char *argv[])
{
    int my_rank;       /* rank of process */
    MPI_Status status; /* return status for receive */

    /* start up MPI */
    MPI_Init(&argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        int x = 8;
        double t1 = MPI_Wtime();
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        double t2 = MPI_Wtime();
        printf("t2-t1 = %f\n", (t2-t1)/2);
    } else {
        int y;
        MPI_Recv(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        y *= 5;
        MPI_Send(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    /* shut down MPI */
    MPI_Finalize();

    return 0;
}
