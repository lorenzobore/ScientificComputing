#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 100000000
#define NUM_THREADS 4 // Or set via environment variable

int main() {
    double *data;
    double sum = 0.0;
    int i;

    // Allocate and initialize array (e.g., with some physics data)
    data = (double*)malloc(ARRAY_SIZE * sizeof(double));
    if (data == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }
    for (i = 0; i < ARRAY_SIZE; ++i) {
        data[i] = (double)i * 0.1 + 1.0; // Example data
    }

    // Set the number of threads for the next parallel region
    omp_set_num_threads(NUM_THREADS);

    double start_time = omp_get_wtime(); // Get wall clock time

    // Parallel region starts here
    #pragma omp parallel
    {
        // The 'for' construct divides loop iterations among threads
        // 'reduction(+:sum)' handles summing partial sums from each thread correctly
        #pragma omp for reduction(+:sum)
        for (i = 0; i < ARRAY_SIZE; ++i) {
            sum += data[i];
        }
    } // Parallel region ends, implicit barrier

    double end_time = omp_get_wtime();

    printf("Sum = %.2f\n", sum);
    printf("Time taken (parallel) = %f seconds\n", end_time - start_time);

    // For comparison: Serial summation
    sum = 0.0;
    start_time = omp_get_wtime();
    for (i = 0; i < ARRAY_SIZE; ++i) {
        sum += data[i];
    }
    end_time = omp_get_wtime();
    printf("Sum (serial) = %.2f\n", sum);
    printf("Time taken (serial) = %f seconds\n", end_time - start_time);


    free(data);
    return 0;
}