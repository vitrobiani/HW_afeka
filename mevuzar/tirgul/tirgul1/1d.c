#include "/home/vitrobiani/.nix-profile/include/mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*
 * one master sends ints to his slaves for them to compare to 0 and return the answer to him
 */
int main(int argc, char *argv[])
{
    srand(time(0));
    int my_rank;       /* rank of process */
    MPI_Status status; /* return status for receive */
    int numprocs;
    int master = rand();

    /* start up MPI */
    MPI_Init(&argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    master = abs(master % numprocs);
    // printf("master is: %d\n", master);

        int arr[numprocs-1];
    if (my_rank == master) {
        double t1 = MPI_Wtime();
        for (int i = 0; i < numprocs; i++) {
            if (i == master) {
                continue;
            }
            int x = rand() * ((rand() % 2 == 0) ? -1 : 1);
            MPI_Send(&x, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            // printf("master sending %d to %d\n", x, i);
        }
        for (int i = 0, j = 0; i < numprocs; i++) {
            if (i == master) {
                continue;
            }
            int x;
            MPI_Recv(&x, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            // printf("master recieved %d from slave number %d\n", x, i);
            arr[j++] = x;
        }
        double t2 = MPI_Wtime();
        printf("t2-t1 = %f\n", t2-t1);
    } else {
        int y;
        MPI_Recv(&y, 1, MPI_INT, master, 0, MPI_COMM_WORLD, &status);
        // printf("Im %d and recieved %d from master\n", my_rank, y);
        int b = y > 0;
        MPI_Send(&b, 1, MPI_INT, master, 0, MPI_COMM_WORLD);
        // printf("Im %d and sent %d to master\n", my_rank, b);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if (my_rank == master) {
        for (int i = 0; i < numprocs-1; i++) {
            printf("%s ", (arr[i]) ? "True" : "False");
        }
    }

    /* shut down MPI */
    MPI_Finalize();

    return 0;
}
