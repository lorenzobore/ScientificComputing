#include <stdio.h>
#include <omp.h> // OpenMP header file

int main() {
    // This pragma defines a parallel region.
    // Code within this block will be executed by multiple threads.
    #pragma omp parallel
    {
        // omp_get_thread_num() returns the unique ID of the current thread.
        // omp_get_num_threads() returns the total number of threads in the parallel region.
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        printf("Hello from thread %d of %d\n", thread_id, num_threads);
    } // End of the parallel region. Implicit barrier here.

    printf("Back to serial execution.\n");

    return 0;
}