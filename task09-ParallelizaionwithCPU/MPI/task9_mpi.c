#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;
    const int N = 8; 
    float a = 3.0f;  // Scalar multiplier

    float *x = NULL, *y = NULL, *dd = NULL;
    float *local_x, *local_y, *local_dd;
    int chunk;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (N % size != 0) {
        if (rank == 0) {
            printf("Vector size %d must be divisible by number of processes %d\n", N, size);
        }
        MPI_Finalize();
        return 1;
    }

    chunk = N / size;

    // Allocate local chunks
    local_x = (float*)malloc(chunk * sizeof(float));
    local_y = (float*)malloc(chunk * sizeof(float));
    local_dd = (float*)malloc(chunk * sizeof(float));

    // Root process initializes full vectors
    if (rank == 0) {
        x = (float*)malloc(N * sizeof(float));
        y = (float*)malloc(N * sizeof(float));
        dd = (float*)malloc(N * sizeof(float));

        for (int i = 0; i < N; i++) {
            x[i] = i * 1.0f;
            y[i] = i * 2.0f;
        }
    }

    // Scatter vectors x and y to all processes
    MPI_Scatter(x, chunk, MPI_FLOAT, local_x, chunk, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, chunk, MPI_FLOAT, local_y, chunk, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Perform computation: dd = a*x + y
    for (int i = 0; i < chunk; i++) {
        local_dd[i] = a * local_x[i] + local_y[i];
    }

    // Gather the result
    MPI_Gather(local_dd, chunk, MPI_FLOAT, dd, chunk, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Root process prints the result
    if (rank == 0) {
        printf("Result vector dd = a*x + y:\n");
        for (int i = 0; i < N; i++) {
            printf("%.2f ", dd[i]);
        }
        printf("\n");
        free(x);
        free(y);
        free(dd);
    }

    free(local_x);
    free(local_y);
    free(local_dd);

    MPI_Finalize();
    return 0;
}
