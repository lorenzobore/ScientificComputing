#include <stdio.h>
#include <omp.h>
#include <unistd.h> // For sleep()

void task_A() {
    printf("Thread %d executing Task A\n", omp_get_thread_num());
    sleep(1); // Simulate work
}

void task_B() {
    printf("Thread %d executing Task B\n", omp_get_thread_num());
    sleep(2); // Simulate work
}

void task_C() {
    printf("Thread %d executing Task C\n", omp_get_thread_num());
    sleep(1); // Simulate work
}

int main() {
    omp_set_num_threads(3); // Ensure enough threads for tasks

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            task_A();

            #pragma omp section
            task_B();

            #pragma omp section
            task_C();
        } // End of sections
    } // End of parallel region

    double end_time = omp_get_wtime();
    printf("All tasks completed in %f seconds.\n", end_time - start_time);

    return 0;
}