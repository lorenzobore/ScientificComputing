#include <stdio.h>
#include <stdlib.h>
#include <float.h>  
#include <math.h>
#include <time.h>


// Function to compare two floating-point numbers with machine precision
int compare_floats(float a, float b, float epsilon) {
    return fabs(a - b) < epsilon;  // Return true if difference is less than epsilon
}


int main() {

    // Initialize the scalar and vectors
    double a = 3.0; 
    int N[3] = {10, 1000000, 100000000};

    // Iterate over each element in N
    for (int i = 0; i < 3; i++) {

        // Record start time
        clock_t start = clock();

        // Dynamically allocate memory for the array based on N[i]
        float *x = (float*) malloc(N[i] * sizeof(float));  // Array of size N[i]
        float *y = (float*) malloc(N[i] * sizeof(float));  // Array of size N[i]
        float *temp = (float*) malloc(N[i] * sizeof(float));  // Array of size N[i]
        float *d = (float*) malloc(N[i] * sizeof(float));  // Array of size N[i]

        float *error = (float*) malloc(N[i] * sizeof(float)); 

        // Check if memory allocation was successful
        if (x == NULL || y == NULL || temp == NULL || d == NULL) {
            printf("Memory allocation failed for N[%d] = %d!\n", i, N[i]);
            return 1;
        }

        // Initialize the array with values
        for (int j = 0; j < N[i]; j++) {
            x[j] = 0.1;  
            y[j] = 7.1;
            error[j] = 0;
        }

        // Compute multiplication a*x result
        int equal_mult = 0;  
        int comparison = 1;
        for (int j = 0; j < N[i]; j++) {
            temp[j] = a*x[j];
            error[j] = a*FLT_EPSILON;
            comparison = compare_floats(temp[j], 0.3, error[j]);
            if (!comparison) {
                equal_mult = 1;  
                break;    
            }
            
        }

        // Print the result of the check
        if (equal_mult) {
            printf("Almeno un valore di temp non è uguale a 0.3\n");
        }

        // Compute addition
        int equal_sum = 0; 
        comparison = 1;
        for (int j = 0; j < N[i]; j++) {
            d[j] = temp[j] + y[j];
            error[j] = sqrt(pow(error[j],2) + pow(FLT_EPSILON,2)); //compile with gcc task2.c -o task2.exe -lm
            comparison = compare_floats(d[j], 7.4, error[j]);
            if (!comparison) {
                equal_sum = 1;  
                break;    
            }
        }

        // Print the result of the check
        if (equal_sum) {
            printf("Almeno un valore di d non è uguale a 7.4\n");
        }

        // Free the allocated memory after use
        free(x);
        free(y);
        free(temp);
        free(d);

        // Record end time
        clock_t end = clock();

        // Calculate the time taken
        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

        int n_operations=0;
        n_operations = N[i] + N[i];
        printf("Computazione corretta per n=%d!\n",N[i]);
        printf("%d operations in %.6f sec\n\n",n_operations,time_taken);

    }

    printf("\n");
    N[0] = 10; 
    N[1] = 100;
    N[2] = 1000;

    // Iterate over each element in N
    for (int i = 0; i < 3; i++) {

        int n = 0;
        n = (int) N[i];

        // Record start time
        clock_t start = clock();

        // Allocate memory for an array of pointers (for rows)
        float **A = (float **) malloc(n * sizeof(float *));
        float **B = (float **) malloc(n * sizeof(float *));
        float **C = (float **) malloc(n * sizeof(float *));

        float **error_matrix = (float**) malloc(n * sizeof(float *)); 

        if (A == NULL || B == NULL || C == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        // Allocate memory for each row (array of floats)
        for (int j = 0; j < n; j++) {
            A[j] = (float *) malloc(n * sizeof(float));
            B[j] = (float *) malloc(n * sizeof(float));
            C[j] = (float *) malloc(n * sizeof(float));
            error_matrix[j] = (float *) malloc(n * sizeof(float));

            if (A[j] == NULL || B[j] == NULL || C[j] == NULL || error_matrix[j] == NULL) {
                printf("Memory allocation failed for row %d!\n", j);
                return 1;
            }
        }

        // Initialize the array with values
        for (int j = 0; j < n; j++) {
            for (int k=0; k < n; k++) {
                A[j][k] = 3.0;
                B[j][k] = 7.1;
                C[j][k] = 0.0;
                error_matrix[j][k] = 0.0;
            }
            
        }

        // Compute matrix-matrix multiplication
        float exp = 0.0;
        int comparison = 1;
        exp = n * 21.3;
        int equal = 0;
        float new_error = 0.0;
        
        for (int r=0; r < n; r++) {
            for (int s=0; s < n; s++) {
                for (int t=0; t < n; t++) {
                    C[r][s] = C[r][s] + A[r][t] * B[t][s];
                    new_error = (FLT_EPSILON * A[r][t] + FLT_EPSILON * B[t][s]);
                    error_matrix[r][s] = sqrt(pow(error_matrix[r][s],2) + pow(new_error,2)); 
                }
                
                comparison = compare_floats(C[r][s], exp, n*n*error_matrix[r][s]);
                if (!comparison) {
                    equal = 1;  
                    break;    
                }
            }
        }

        // Print the result of the check
        if (equal) {
            printf("Almeno un valore di C non è uguale a %.6f\n",exp);
        }

       // Step 5: Free the allocated memory
        for (int j = 0; j < n; j++) {
            free(A[j]);
            free(B[j]);
            free(C[j]);
        }
        free(A);
        free(B);
        free(C);

        // Record end time
        clock_t end = clock();

        // Calculate the time taken
        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

        int n_operations=0;
        n_operations = n * n * n ;
        printf("Computazione corretta per n=%d!\n",N[i]);
        printf("%d operations in %.6f sec\n\n",n_operations,time_taken);

    }

    return 0;
}
