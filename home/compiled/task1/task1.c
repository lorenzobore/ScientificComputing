#include <stdio.h>

int main() {
    // Initialize the scalar and vectors
    double a = 3.0;  // Scalar value
    int N = 20;      // Dimension of the vectors
    double x[20];    // Vector x
    double y[20];    // Vector y
    double z[20];    // Resultant vector z
    
    // Initialize vector x with all elements = 1
    for (int i = 0; i < N; i++) {
        x[i] = 1.0;
    }

    // Initialize vector y with all elements = 4
    for (int i = 0; i < N; i++) {
        y[i] = 4.0;
    }

    // Calculate z = a * x + y
    for (int i = 0; i < N; i++) {
        z[i] = a * x[i] + y[i];
    }

    // Write the result to a text file
    FILE *file = fopen("result.txt", "w");
    if (file == NULL) {
        printf("Error opening the file for writing.\n");
        return 1;
    }

    // Write the result vector z to the file
    for (int i = 0; i < N; i++) {
        fprintf(file, "z[%d] = %lf\n", i, z[i]);
    }

    // Close the file
    fclose(file);

    printf("Result has been written to result.txt.\n");

    return 0;
}
