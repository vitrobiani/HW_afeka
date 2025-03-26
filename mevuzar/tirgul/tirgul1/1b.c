#include "/home/vitrobiani/.nix-profile/include/mpi.h"
#include <stdio.h>

/*
 * send a variable between processes
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
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("bef x = %d\n", x);
        MPI_Recv(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        printf("aft x = %d\n", x);
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
