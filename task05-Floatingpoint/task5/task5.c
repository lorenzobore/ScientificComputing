#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_statistics.h>

double gsl_vector_sum(const gsl_vector *v) {
    double sum = 0.0;
    for (size_t i = 0; i < v->size; ++i) {
        sum += gsl_vector_get(v, i);
    }
    return sum;
}


// Funzione per calcolare la somma utilizzando l'algoritmo di Kahan
double kahan_sum(const double* valori, size_t n) {
    double somma = 0.0;
    double compensazione = 0.0; // Compensazione per l'errore di arrotondamento

    for (size_t i = 0; i < n; i++) {
        double y = valori[i] - compensazione;
        double t = somma + y;
        compensazione = (t - somma) - y;
        somma = t;
    }

    return somma;
}

int main(){

    // Allocate memory for vector
    int length = 4;
    double *vector;
    vector = (double *)malloc(length * sizeof(double));

    // Define each element
    vector[0] = 1.0;
    vector[1] = 1e16;
    vector[2] = -1e16;
    vector[3] = -0.5;

    printf("Vector instantiated as: [%.20g,%.20g,%.20g,%.20g]\n",vector[0],vector[1],vector[2],vector[3]);

    // Calculate Sum with a for loop
    double result1 = 0;
    for (int i=0; i<length; i++) {
        result1 = result1 + vector[i];
    }

    printf("Result from for loop = %.20g\n",result1);
    

    // Ripeti con GSL
    gsl_vector *vec = gsl_vector_alloc(4);

    // Inizializza gli elementi
    gsl_vector_set(vec, 0, 1.0);
    gsl_vector_set(vec, 1, 1.0e16);
    gsl_vector_set(vec, 2, -1.0e16);
    gsl_vector_set(vec, 3, -0.5);

    // Calcola la somma
    double sum = gsl_vector_sum(vec);

    // Stampa il risultato
    printf("Somma degli elementi con GSL = %.20g\n", sum);

    // Libera la memoria
    gsl_vector_free(vec);

    // Usa
    double result3 = kahan_sum(vector,length);
    free(vector);

    printf("Result with KahanSum = %.20g\n",result3);
    printf("--------------------\n\n");


    // TRY AGAIN WITH OTHER VALUES

    // Allocate memory for vector
    double *new_vector;
    new_vector = (double *)malloc(length * sizeof(double));

    // Define each element
    new_vector[0] = 1.0;
    new_vector[1] = 1e16;
    new_vector[2] = -1e16;
    new_vector[3] = -0.5;

    printf("Vector instantiated as: [%.20g,%.20g,%.20g,%.20g]\n",new_vector[0],new_vector[1],new_vector[2],new_vector[3]);

   
    // Calculate Sum with a for loop
    double new_result1 = 0;
    for (int i=0; i<length; i++) {
        new_result1 = new_result1 + new_vector[i];
    }

    printf("Result from for loop = %.20g\n",new_result1);
    

    // Ripeti con GSL
    gsl_vector *new_vec = gsl_vector_alloc(4);

    // Inizializza gli elementi
    gsl_vector_set(new_vec, 0, 1.0);
    gsl_vector_set(new_vec, 1, 1.0e15);
    gsl_vector_set(new_vec, 2, -1.0e15);
    gsl_vector_set(new_vec, 3, -0.5);

    // Calcola la somma
    double new_sum = gsl_vector_sum(new_vec);

    // Stampa il risultato
    printf("Somma degli elementi con GSL = %.20g\n", new_sum);

    // Libera la memoria
    gsl_vector_free(new_vec);

    // Usa
    double new_result3 = kahan_sum(new_vector,length);
    free(new_vector);

    printf("Result with KahanSum = %.20g\n",new_result3);
    printf("--------------------\n\n");






    // New DAXPY
    const size_t N = 10000; 
    const double A = 1.0;

    // Allocate vectors
    gsl_vector *x = gsl_vector_alloc(N);
    gsl_vector *y = gsl_vector_alloc(N);
    gsl_vector *D = gsl_vector_alloc(N);

    // Initialize random number generator
    gsl_rng *rng = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set(rng, 3); 

    // Fill vectors with standard Gaussian random numbers
    for (size_t i = 0; i < N; ++i) {
        double xi = gsl_ran_gaussian(rng, 1.0);  // mean = 0, std = 1
        double yi = gsl_ran_gaussian(rng, 1.0);
        gsl_vector_set(x, i, xi);
        gsl_vector_set(y, i, yi);
    }


    // Compute D = A * x
    gsl_vector_memcpy(D, x);           // D = x
    gsl_vector_scale(D, A);           // D = A * x
    gsl_vector_add(D, y);             // D = A * x + y

    // Compute mean and standard deviation of D
    double mean = gsl_stats_mean(D->data, 1, D->size);
    double std_dev = gsl_stats_sd(D->data, 1, D->size);

    printf("\nStats for vector D:\n");
    printf("Mean: %.5f\n", mean);
    printf("Standard Deviation: %.5f\n", std_dev);

    // Free memory
    gsl_vector_free(x);
    gsl_vector_free(y);
    gsl_vector_free(D);
    gsl_rng_free(rng);

    return 0;
}