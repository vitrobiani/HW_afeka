// #include <mpi.h>
#include "/home/vitrobiani/.nix-profile/include/mpi.h"
#include <math.h>
#include <stdio.h>
#define HEAVY  100000
#define SIZE   30

// This function performs heavy computations, 
// its run time depends on x and y values
// DO NOT change the function
double heavy(int x, int y) {
    int i, loop;
    double sum = 0;
    if ((x == 3 && y == 3) || (x == 3 && y == 5) ||
        (x == 3 && y == 7) || (x == 20 && y == 10))
        loop = 200;
    else
        loop = 1;
    for (i = 1; i < loop * HEAVY; i++)
        sum += cos(exp(cos((double)i / HEAVY)));
    return  sum;
}

// Sequential code to be parallelized
int main(int argc, char** argv) {
    int size = SIZE;
    double start_time, end_time;

    int rank, num_procs;
    MPI_Init(&argc, &argv);  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    start_time = MPI_Wtime(); // Start timing

    double local_answer = 0;

    int total_tasks = size * size;
    for (int idx = rank; idx < total_tasks; idx += num_procs) {
        int x = idx / size;
        int y = idx % size;
        local_answer += heavy(x, y);
    }

    double global_answer = 0;
    MPI_Reduce(&local_answer, &global_answer, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Final answer = %e\n", global_answer);
    }

    end_time = MPI_Wtime(); // End timing
    printf("Execution time: %f seconds\n", end_time - start_time);

    MPI_Finalize();
    return 0;
}
