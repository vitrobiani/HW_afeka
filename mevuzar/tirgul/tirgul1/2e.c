#include "/home/vitrobiani/.nix-profile/include/mpi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

/*
 * one master sends ints to his slaves for them to compare to 0 and return the
 * answer to him
 */
int main(int argc, char *argv[]) {
    // srand(time(0));
    int my_rank;       /* rank of process */
    MPI_Status status; /* return status for receive */
    int numprocs;
    int master = rand();
    int vec1[SIZE];
    int vec2[SIZE];

    /* start up MPI */
    MPI_Init(&argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    master = abs(master % numprocs);
    // printf("master is: %d\n", master);

    int mult = SIZE / (numprocs - 1);
    if (my_rank == master) {
        // printf("master = %d\n", master);
        printf("vec1: ");
        for (int i = 0; i < SIZE; i++) {
            vec1[i] = rand() % 10;
            printf("%d ", vec1[i]);
        }
        printf("\nvec2: ");
        for (int i = 0; i < SIZE; i++) {
            vec2[i] = rand() % 10;
            printf("%d ", vec2[i]);
        }
        double t1 = MPI_Wtime();
        for (int i = 0; i < numprocs; i++) {
            if (i == master) {
                continue;
            }
            // printf("master sending vectors to %d\n", i);
            MPI_Send(vec1, SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(vec2, SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        int y = 1;
        for (int i = 0, j = 0; i < numprocs; i++) {
            if (i == master) {
                continue;
            }
            int x;
            MPI_Recv(&x, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            // printf("master recieved %d from slave number %d\n", x, i);
            y += x;
        }
        double t2 = MPI_Wtime();
        printf("y = %d\n", y);
        printf("t2-t1 = %f\n", t2-t1);
    } else {
        // int *v1, *v2;
        MPI_Recv(vec1, SIZE, MPI_LONG, master, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(vec2, SIZE, MPI_LONG, master, 0, MPI_COMM_WORLD, &status);
        // printf("Im %d and recieved vectors from master\n", my_rank);
        int m = 0;
        int i = (my_rank > master) ? mult * (my_rank - 1) : mult * my_rank;
        int bound = (my_rank == numprocs - 1 ||
                     (master == (numprocs - 1) && my_rank == (numprocs - 2)))
                        ? SIZE
                        : i + mult;
        printf("Im %d and I sum %d to %d\n", my_rank, i, bound);
        for (; i < bound; i++) {
            m += vec1[i] * vec2[i];
        }
        MPI_Send(&m, 1, MPI_INT, master, 0, MPI_COMM_WORLD);
    }

    /* shut down MPI */
    MPI_Finalize();

    return 0;
}
