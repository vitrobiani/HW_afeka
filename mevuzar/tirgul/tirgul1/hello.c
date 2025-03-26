#include "/home/vitrobiani/.nix-profile/include/mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int x, y;
    int my_rank;       /* rank of process */
    int p;             /* number of processes */
    MPI_Status status; /* return status for receive */
    double t1, t2;

    /* start up MPI */
    MPI_Init(&argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* find out number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (my_rank == 0) {
        x = 7;
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        t1 = MPI_Wtime();
        printf("The new value of x = %d\n", x);
    } else {
        MPI_Recv(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        t2 = MPI_Wtime();
    }

    if (my_rank == 0) {
        x = 7;
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        t1 = MPI_Wtime();
        printf("The new value of x = %d\n", x);
    } else {
        MPI_Recv(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        t2 = MPI_Wtime();
    }

    /* shut down MPI */
    MPI_Finalize();

    printf("time: %f\n", (t2 - t1));
    return 0;
}
