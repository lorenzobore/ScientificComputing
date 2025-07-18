#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <float.h>
#include <stdbool.h>


bool assert_almost_equal(float val1, float val2, float epsilon){
    return (fabs((val1) - (val2)) < (epsilon));
}

int main(){

    // Allocate memory for variables
    int N=100;
    int chunk_size=8;
    float a=3;
    float *x = (float*) malloc(N * sizeof(float));
    float *y = (float*) malloc(N * sizeof(float));
    float *result = (float*) malloc(N * sizeof(float));

    //Initialize data
    for (int i=0;i<N;i++){
        x[i] = 0.1;
        y[i] = 7.1;
    }

    // Calculate number of chunks
    int n_chunks = (int)ceil((double)N/chunk_size);
    int flat_idx=0;
    printf("N points = %d\n",N);
    printf("chunk_size = %d\n",chunk_size);
    printf("n_chunks = %d\n",n_chunks);

    float *chunk_sums = (float*) malloc(n_chunks * sizeof(float));

    //Iterate over different chunks
    for (int chunk_idx=0;chunk_idx<n_chunks;chunk_idx++){
        //Iterate over elements inside chunks
        float batch_sum = 0;
        for (int elem_idx=0;elem_idx<chunk_size;elem_idx++){
            flat_idx = chunk_size*chunk_idx + elem_idx;
            if (flat_idx==N){
                break;
            }
            result[flat_idx] = a * x[flat_idx] + y[flat_idx];
            batch_sum += result[flat_idx];
        }
        chunk_sums[chunk_idx] = batch_sum;
    }

    //Sum over partial sums
    float total_from_partial = 0;
    for (int i=0;i<n_chunks;i++){
        total_from_partial += chunk_sums[i];
    }

    //Check the correctness of the result
    float total_sum = 0;
    for (int i=0;i<N;i++){
        bool check = assert_almost_equal(result[i],7.4,2*FLT_EPSILON);
        if (!check){
            printf("Wrong result! %.4f\n",result[i]);
        }
        total_sum += result[i];
    }

    //
    printf("Correct result : %.3f\n",result[0]);
    printf("Total sum from partials : %.3f\n",total_from_partial);
    printf("Total sum : %.3f\n",total_sum);
    
    free(x);
    free(y);
    free(result);
    free(chunk_sums);

}