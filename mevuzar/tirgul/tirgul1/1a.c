#include "/home/vitrobiani/.nix-profile/include/mpi.h"
#include <stdio.h>

/*
 * each process just prints out his rank
 */
int main(int argc, char *argv[])
{
    int my_rank;       /* rank of process */

    /* start up MPI */
    MPI_Init(&argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    printf("This is my rank: %d\n", my_rank);

    /* shut down MPI */
    MPI_Finalize();

    return 0;
}
