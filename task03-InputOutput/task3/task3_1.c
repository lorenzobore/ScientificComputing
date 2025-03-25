#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // Insert input from command line
    int N;
    printf("Insert length of vectors N:\n");
    scanf("%d",&N);
    printf("Value inserted: N=%d\n",N);
    printf("--------------------\n\n");

    // Create vectors: allocate memory
    float *x = (float*) malloc(N * sizeof(float));  
    float *y = (float*) malloc(N * sizeof(float));  

    // Check if memory allocation was successful
    if (x == NULL || y == NULL) {
        printf("Memory allocation failed for N = %d!\n", N);
        return 1;
    }

    // Initialize vector values
    for (int i = 0; i < N; i++) {
        x[i] = 0.1;
        y[i] = 7.1;
    }

    // Ask for folder
    printf("Insert folder:\n");
    char folder[10];
    scanf("%s", folder);
    printf("Value inserted for folder: %s\n",folder);
    printf("--------------------\n\n");

    // Write filenames
    char N_char[8]; // converts integer to char
    sprintf(N_char, "%d", N);

    char name[16] = "vector_N";
    char x_suffix[16] = "_x.dat";
    char y_suffix[16] = "_y.dat";

    // Conctenate strings
    char x_filename[64] = "";
    strcat(x_filename,folder);
    strcat(x_filename,name);
    strcat(x_filename,N_char);
    strcat(x_filename,x_suffix);

    // Open file and write values on it
    FILE *fp_x = fopen(x_filename, "w");
    if (fp_x != NULL){
        for (int i=0; i<N; i++){
            char format[16]="%f\n";
            float value=x[i];
            fprintf(fp_x, format, value);
        }
    }
    else{
        printf("ERROR: file %s did not open!",x_filename);
    }
    int fclose(FILE *fp_x);

    // Concatenate strings
    char y_filename[64] = "";
    strcat(y_filename,folder);
    strcat(y_filename,name);
    strcat(y_filename,N_char);
    strcat(y_filename,y_suffix);

    // Open file and write values on it
    FILE *fp_y = fopen(y_filename, "w");
    if (fp_y != NULL){
        for (int i=0; i<N; i++){
            char format[16]="%f\n";
            float value=y[i];
            fprintf(fp_y, format, value);
        }
    }
    else{
        printf("ERROR: file %s did not open!",y_filename);
    }
    int fclose(FILE *fp_y);

    printf("Written File for x: %s\n",x_filename);
    printf("Written File for y: %s\n\n",y_filename);
    printf("--------------------\n\n");


    return 0;
}