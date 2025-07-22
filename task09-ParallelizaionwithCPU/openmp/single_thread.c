#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        // All threads execute this
        printf("Thread %d reporting in.\n", omp_get_thread_num());

        // Only one thread (chosen by the runtime) executes this
        #pragma omp single
        {
            printf("Thread %d (single) is performing a special I/O task.\n", omp_get_thread_num());
        }

        // Only the master thread (ID 0) executes this
        #pragma omp master
        {
            printf("Master thread (%d) is doing some master-only work.\n", omp_get_thread_num());
        }

        // Implicit barrier here due to the end of the parallel region.
        // Threads wait here.
        #pragma omp barrier // Explicit barrier for demonstration

        printf("Thread %d passed the barrier.\n", omp_get_thread_num());

    }
    return 0;
}