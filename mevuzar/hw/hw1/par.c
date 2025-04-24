#include "/home/vitrobiani/.nix-profile/include/mpi.h"
// #include "mpi.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define HEAVY 100000
#define SIZE 40
double heavy(int x, int y);

int main(int argc, char *argv[]) {
    // srand(time(0));
    int my_rank;       /* rank of process */
    MPI_Status status; /* return status for receive */
    int numprocs;
    int x, y;
    int size = SIZE;

    /* start up MPI */
    MPI_Init(&argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    int start_x = (my_rank - 1) * (size / (numprocs-1));
    int bound = my_rank * (size / (numprocs-1));

    if (my_rank == 0) {
        double answer = 0;
        double rcv_buf[numprocs-1];
        // MPI_Gather(NULL, 0, MPI_DOUBLE, rcv_buf, numprocs-1, MPI_DOUBLE, my_rank, MPI_COMM_WORLD);

        for (int i = 1; i < numprocs; i++) {
            MPI_Recv(&rcv_buf[i], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
            printf("rcv_buf[i] = %f\n", rcv_buf[i]);
        }
        for (int i = 0; i < numprocs-1; i++) {
            answer += rcv_buf[i];
        }
        printf("answer = %f\n", answer);
    } else {
        double answer = 0;
        for (int i = start_x; i < bound; i++) {
            for (int j = 0; j < size; j++) {
                answer += heavy(i, j);
            }
        }
        MPI_Send(&answer, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        // MPI_Gather(&answer, 1, MPI_DOUBLE, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
    }

    /* shut down MPI */
    MPI_Finalize();
}

/*
 * static: divide the work load to the numprocs and give each proc his load
 *
 * dynamic: divide the work load into smaller bite size works that will be in a
 * shared workspace and each proc will take a job from the pool
 *
 */

// This function performs heavy computations,
// its run time depends on x and y values
// DO NOT change the function
double heavy(int x, int y) {
    int i, loop;
    double sum = 0;
    if ((x == 3 && y == 3) || (x == 3 && y == 5) || (x == 3 && y == 7) ||
        (x == 20 && y == 10))
        loop = 200;
    else
        loop = 1;
    for (i = 1; i < loop * HEAVY; i++)
        sum += cos(exp(cos((double)i / HEAVY)));
    return sum;
}
