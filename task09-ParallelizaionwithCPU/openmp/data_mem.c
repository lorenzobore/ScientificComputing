#include <stdio.h>
#include <omp.h>

int main() {
    int shared_var = 10;
    int private_var_orig = 20;
    int firstprivate_var_orig = 30;
    int i; // Loop variable

    omp_set_num_threads(2);

    #pragma omp parallel default(none) \
                         shared(shared_var) \
                         private(i, private_var_orig) \
                         firstprivate(firstprivate_var_orig)
    {
        int thread_id = omp_get_thread_num();

        // shared_var: All threads see and can modify the same variable (potential race condition if not careful)
        // For demonstration, let's increment it carefully (though reduction is better for sums)
        #pragma omp critical // Ensure only one thread modifies shared_var at a time
        shared_var += 5;

        // private_var_orig: Each thread gets an uninitialized local copy.
        // Let's assign its thread_id.
        private_var_orig = thread_id * 100;

        // firstprivate_var_orig: Each thread gets a local copy initialized with the original value (30).
        firstprivate_var_orig += thread_id * 10;

        printf("Thread %d: shared_var = %d, private_var_orig = %d, firstprivate_var_orig = %d\n",
               thread_id, shared_var, private_var_orig, firstprivate_var_orig);

        // i is implicitly private in an omp for loop if declared outside the parallel region and not listed
        // or explicitly made private. Here we made it private explicitly in the parallel directive.
        #pragma omp for
        for (i = 0; i < 2; ++i) {
            printf("Thread %d: i = %d (loop iteration)\n", thread_id, i);
        }

    } // End of parallel region

    printf("After parallel region:\n");
    printf("shared_var = %d (expected: 10 + 5*num_threads)\n", shared_var);
    printf("private_var_orig = %d (original value, private copies are gone)\n", private_var_orig);
    printf("firstprivate_var_orig = %d (original value, private copies are gone)\n", firstprivate_var_orig);

    return 0;
}