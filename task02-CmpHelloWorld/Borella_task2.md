# Task 2 - Computational Hello World

Codes also available at https://github.com/lorenzobore/ScientificComputing. 

## 1) float * vector + vector

### Inerpreted language - Julia

Source Code 
```
    N = [10,10^6,10^8]
    a = 3

    for n in N 

        elapsed_time = @elapsed begin

            #initialize vectors
            x = fill(0.1,n)  
            y = fill(7.1,n)  

            #check
            @assert length(x)==n "ERROR: wrong initialization of x!"
            @assert length(y)==n "ERROR: wrong initialization of y!"

            #compute vector x scalar
            temp = a * x

            @assert length(temp)==n "ERROR: wrong dimension in vector-scalar multiplication"
            @assert all(abs.(temp .- 0.3) .== eps(0.3)) "ERROR: wrong computation of a * x"

            #compute final result 
            d = temp + y
            @assert length(d)==n "ERROR: wrong dimension in vector-vector sum"
            @assert all(abs.(d .- 7.4) .== eps(7.4)) "ERROR: wrong computation of a * x + y"

        end
        println("Correct computation of d=a*x+y for N=$n ($elapsed_time sec)")
    end
```

Of Output:

```
Correct computation of d=a*x+y for N=10 (0.43156412 sec)
Correct computation of d=a*x+y for N=1000000 (0.166804257 sec)
Correct computation of d=a*x+y for N=100000000 (6.087319162 sec)

```

### Compiled language - C
Source Code: 

```
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
            error[j] = sqrt(pow(error[j],2) + pow(FLT_EPSILON,2)); 
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

    return 0;
}

```

Of Output:
```
Computazione corretta per n=10!
20 operations in 0.000660 sec

Computazione corretta per n=1000000!
2000000 operations in 0.117938 sec

Computazione corretta per n=100000000!
200000000 operations in 8.361539 sec
```

## 2) matrix * matrix

### Interpreted language - julia
Source Code:
```
N=[10, 100, 10000]

for n in N

    elapsed_time = @elapsed begin
        #initialize matrices
        A = fill(3.0, (n,n))
        B = fill(7.1, (n,n))

        #compute matrix-amtrix multiplication 
        C = A * B 

        @assert size(C)==(n,n) "ERROR: wrong size after multiplicaiton"
        @assert all(abs.(C .- n*21.3) .<= n*eps(n*21.3)) "ERROR: wrong matrix matrix multiplication"
    end 

    println("Correct computation of C = AB, for N=$n ($elapsed_time sec)")
end
```
Of output:
```
Correct computation of C = AB, for N=10 (2.542420994 sec)
Correct computation of C = AB, for N=100 (0.014441042 sec)
Correct computation of C = AB, for N=10000 (69.723012203 sec)
```

### Compilled language - C
Source Code:
```
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

```
Of Output:
```
Computazione corretta per n=10!
1000 operations in 0.000145 sec

Computazione corretta per n=100!
1000000 operations in 0.200144 sec

Computazione corretta per n=1000!
1000000000 operations in 140.401717 sec
```

## 3) Questions

### I - Did you find any problems in running the codes for some N. If so, do you have an idea why?

I didn't find any problem when running point-1 for N=10, 10^6, 10^8. We only have N multiplications + N sums to perform. For point-2 instead, the amount of operations grow as n^3. We need to perform N multiplications and N sums in order to compute each of the n^2 elemetns of matrix C. The matrix-matrix multiplication takes more time.

### II - Where you able to test correctly the sum and product of points 1-3? If so, how? If not, what was the problem?

You can only test the correctness of operations if you consider machine precision. Since Boolean operator == will not work when comparing float values, the best option is to compare the absolute difference between your result and what you expect it to be, checking that is fall within a pre-defined epsilon.

