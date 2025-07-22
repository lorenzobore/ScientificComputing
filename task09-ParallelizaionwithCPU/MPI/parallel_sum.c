#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Broken code does not run correctly
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Each process creates a local sum
    srand(time(NULL) + world_rank); // Seed random number generator differently for each process
    double local_value = (double)rand() / RAND_MAX * 100.0; // Example local value
    double global_sum;

    printf("Process %d has local value: %f\n", world_rank, local_value);

    // Reduce all local_value's into global_sum on process 0
    // MPI_SUM is the operation to perform
    MPI_Reduce(&local_value, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Process 0 prints the global sum
    if (world_rank == 0) {
        printf("Total sum computed on process 0: %f\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}