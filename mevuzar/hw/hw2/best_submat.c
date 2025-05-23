#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>
#include <time.h>

#define MAX_N 15
#define MAX_M 15
#define MAX_K 20

int A[MAX_N][MAX_M];

double compute_log_product(int K, int i, int j, int N, int M) {
    double log_sum = 0.0;
    for (int x = 0; x < K; x++) {
        for (int y = 0; y < K; y++) {
            int val = A[i + x][j + y];
            if (val % 2 == 1) {
                log_sum += log((double)val);
            }
        }
    }
    return log_sum;
}

void print_mat() {
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_M; j++) {
            printf(" %2d", A[i][j]);
        }
        printf("\n");
    }
}

void fill_matrix(int N, int M) {
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            A[i][j] = rand() % 100;
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Status status;
    int N = MAX_N, M = MAX_M, K = 2;
    int local_start, local_end;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    start_time = MPI_Wtime();

    if (rank == 0)
        fill_matrix(N, M);

    // Broadcast matrix and size
    MPI_Bcast(&A[0][0], MAX_N * MAX_M, MPI_INT, 0, MPI_COMM_WORLD);

    int total_rows = N - K + 1;
    int rows_per_process = total_rows / size;
    int extra_rows = total_rows % size;
    
    local_start = rank * rows_per_process + (rank < extra_rows ? rank : extra_rows);
    local_end = local_start + rows_per_process + (rank < extra_rows ? 1 : 0);

    double local_max_log = -1.0;
    int max_i = -1, max_j = -1;

    // doing the heavy task (computing the log product) in parallel
    #pragma omp parallel for collapse(2) num_threads(4)
    for (int i = local_start; i < local_end; i++) {
        for (int j = 0; j <= M - K; j++) {
            double log_sum = compute_log_product(K, i, j, N, M);
            // to avoid race conditions this needs to be critical
            #pragma omp critical
            {
                if (log_sum > local_max_log) {
                    local_max_log = log_sum;
                    max_i = i;
                    max_j = j;
                }
            }
        }
    }

    // Chcking all MPI process to see which one has the global best result
    double global_result = 0;
    double global_i = 0;
    double global_j = 0;

    if (rank == 0) {
        global_result = local_max_log;
        global_i = max_i;
        global_j = max_j;
        for (int k = 1; k < size; k++) {
            double temp_buf[3] = {0,0,0};
            MPI_Recv(&temp_buf, 3, MPI_DOUBLE, k, 0, MPI_COMM_WORLD, &status); 
            if (temp_buf[0] > global_result) {
                global_result = temp_buf[0];
                global_i = temp_buf[1];
                global_j = temp_buf[2];
            }
        }
    } else {
        double send_info[3] = {local_max_log, max_i, max_j};
        MPI_Send(send_info, 3, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    end_time = MPI_Wtime();

    if (rank == 0) {
        print_mat();
        printf("\nMax log-product: (%f) submatrix starts at (%d, %d)\n", global_result, (int) global_i, (int) global_j);
        printf("Elapsed time: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
