#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h> 
#include <float.h>


float daxpy(int offset,int n_points, float a, float* x, float * y, float* result){
    for (int i=offset; i<n_points;i++){
        result[i] = a*x[i] + y[i];
    }
}

float addition(int N, float* result){
    float sum=0;
    for (int i=0;i<N;i++){
        sum+=result[i];
    }
    return sum;
}

void check_result(int N,float * result,float true_result,float eps){
    for (int i=0;i<N;i++){
        bool check = abs(result[i]-true_result)<eps;
        if (!check){
            printf("Wrong result: %.4f\n",result[i]);
        }
    }
}

void reset_results(int N,float* x, float* y,float * result){
    for (int i=0;i<N;i++){
        x[i]=0.1;
        y[i]=7.1;
        result[i]=0;
    }
}


int main(){

    // Allocate memory for variables
    int N=400000;
    float a=3;
    float *x = (float*) malloc(N * sizeof(float));
    float *y = (float*) malloc(N * sizeof(float));
    float *result = (float*) malloc(N * sizeof(float));
    float true_result = 7.4;

    //Initialize results
    reset_results(N,x,y,result);

    //Serial computation
    double start_time_serial = omp_get_wtime();
    for (int i=0; i<N;i++){
        result[i] = a*x[i] + y[i];
    }
    double end_time_serial = omp_get_wtime();
    printf("Serial computation with N=%d completed in %f seconds.\n\n", N,end_time_serial - start_time_serial);

    //Check and reset results
    check_result(N,result,true_result,FLT_EPSILON);
    reset_results(N,x,y,result);

    // Setup number of threads
    int n_threads = 4;
    omp_set_num_threads(n_threads); // Ensure enough threads for tasks

    // Single Task
    double start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        #pragma omp for
        for (int i=0; i<N;i++){
            result[i] = a*x[i] + y[i];
        }
        //printf("Using thread %d of %d\n", thread_id, num_threads);
        
    } 
    double end_time = omp_get_wtime();
    printf("Single task with N=%d completed in %f seconds.\n\n", N,end_time - start_time);

    //Check and reset results
    check_result(N,result,true_result,FLT_EPSILON);
    reset_results(N,x,y,result);


    // Multiple Tasks
    double start_time0 = omp_get_wtime();
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp sections
        {
            #pragma omp section
            {
                for (int i=0; i<100000;i++){
                    result[i] = a*x[i] + y[i];
                }
                //printf("Using thread %d of %d\n", thread_id, num_threads);
            }

            #pragma omp section
            {
                for (int i=100000; i<200000;i++){
                    result[i] = a*x[i] + y[i];
                }
                //printf("Using thread %d of %d\n", thread_id, num_threads);
            }

            #pragma omp section
            {
                for (int i=200000; i<300000;i++){
                    result[i] = a*x[i] + y[i];
                }
                //printf("Using thread %d of %d\n", thread_id, num_threads);
            }

            #pragma omp section
            {
                for (int i=300000; i<400000;i++){
                    result[i] = a*x[i] + y[i];
                }
                //printf("Using thread %d of %d\n", thread_id, num_threads);
            }
        } 
    } 
    double end_time0 = omp_get_wtime();
    printf("(Shared variables) Multiple tasks task with N=400000 completed in %f seconds.\n\n",end_time0 - start_time0);

    //Check and reset results
    check_result(N,result,true_result,FLT_EPSILON);
    reset_results(N,x,y,result);


    // Multiple Tasks
    double start_time1 = omp_get_wtime();
    int private_thr_id;
    int private_tot_threads;

    #pragma omp parallel default(none) \
                         private(private_thr_id,private_tot_threads)\
                         firstprivate(a,x,y,result)
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        private_thr_id=thread_id;
        private_tot_threads=num_threads;

        #pragma omp sections
        {
            #pragma omp section
            {
                for (int i=0; i<100000;i++){
                    result[i] = a*x[i] + y[i];
                }
                //printf("Using thread %d of %d\n", private_thr_id, private_tot_threads);
            }

            #pragma omp section
            {
                for (int i=100000; i<200000;i++){
                    result[i] = a*x[i] + y[i];
                }
                //printf("Using thread %d of %d\n", private_thr_id, private_tot_threads);
            }

            #pragma omp section
            {
                for (int i=200000; i<300000;i++){
                    result[i] = a*x[i] + y[i];
                }
                //printf("Using thread %d of %d\n", private_thr_id, private_tot_threads);
            }

            #pragma omp section
            {
                for (int i=300000; i<400000;i++){
                    result[i] = a*x[i] + y[i];
                }
                //printf("Using thread %d of %d\n", private_thr_id, private_tot_threads);
            }
        } 
    } 
    double end_time1 = omp_get_wtime();
    printf("(Private variables) Multiple tasks task with N=400000 completed in %f seconds.\n\n",end_time1 - start_time1);

    //Check and reset results
    check_result(N,result,true_result,FLT_EPSILON);
    reset_results(N,x,y,result);


    //Sum of the final vector
    int N1=100000;

    //Serial sum
    float sum = 0;
    double start_time_serial3 = omp_get_wtime();
    for (int i=0; i<N1;i++){
        result[i] = a*x[i] + y[i];
    }
    sum = addition(N1, result);
    double end_time_serial3 = omp_get_wtime();
    printf("Serial sum of N=%d completed in %f seconds.\n", N1, end_time_serial3 - start_time_serial3);
    printf("Sum relative error: %.5f\n\n",abs(sum-7.4*N1)/sum);

    // Multiple Tasks
    int i=0;
    float sum1 = 0;
    double start_time4 = omp_get_wtime();
    #pragma omp parallel 
    {
        #pragma omp for
        for (int i=0; i<N1;i++){
            result[i] = a*x[i] + y[i];
        }

        #pragma omp for reduction(+:sum1)
        for (int i=0;i<N;i++){
            sum1+=result[i];
        }
    } 
    double end_time4 = omp_get_wtime();
    printf("Parallel sum completed in %f seconds.\n",end_time4 - start_time4);
    printf("Sum relative error: %.5f \n\n",abs(sum1-7.4*N1)/sum1);

    free(x);
    free(y);
    free(result);

    return 0;
}