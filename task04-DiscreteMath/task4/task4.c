#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>


double integrand(double x){
    double exponential,cosine;
    exponential = exp(x); 
    cosine = cos(x); 
    return exponential*cosine;
}

double compute_integral(double dx, double *y, int size){

    double result = 0;
    for (int i=0;i<size;i++){
        result +=(y[i+1]+y[i])*dx/2; 
    }
    return result;
}

int main() {

    // Insert input from command line
    int N;
    printf("--------------------\n");
    printf("Insert number of sampling points N:\n");
    scanf("%d",&N);

    double x_inf,x_sup;
    printf("Integrate from:\n");
    scanf("%lf",&x_inf);
    x_sup = M_PI/2;
    printf("To: x_sup=%lf by default\n",x_sup);
   
    printf("--------------------\n\n");

    // Generate x interval and points
    double dx;
    dx = (x_sup - x_inf)/N;
    printf("N = %d points generated in the range [%lf,%lf] with step dx=%lf.\n",N,x_inf,x_sup,dx);

    // Allocare memoria dinamica per x e y
    double *x, *y;
    x = (double *)malloc(N * sizeof(double));
    y = (double *)malloc(N * sizeof(double));
    
    if (x == NULL || y == NULL) {
        perror("Errore nell'allocazione della memoria");
        return 1;
    }

    // Write file of data
    FILE *data_file = fopen("data.txt", "w");
    if (data_file != NULL){
        for (int i=0; i<N; i++){
            double x_single = i*dx;
            double y_single = integrand(x_single);
            char format[16]="%lf %lf\n";
            fprintf(data_file, format, x_single, y_single);
            x[i] = x_single;
            y[i] = y_single;
            //printf("Written x=%lf, y=%lf on file.\n",x[i],y[i]);
        }
    }
    else{
        printf("ERROR: file %s did not open!","data.dat");
    }
    int fclose(FILE *data_file);

    // Compute Integral
    double I;
    I = compute_integral(dx,y,N);
    printf("I = %.16lf\n",I);

    //Answer question 1
    double I_true = (exp(M_PI/2)-1)/2;
    double eps = fabs(I/I_true - 1);
    printf("I=%lf, I_true=%lf, |eps|=%lf considering N=%d sampling points\n",I,I_true,eps,N);
    free(x);
    free(y);

    //Answer question 2 : increase the number of points 
    // Allocare memoria dinamica per x e y
    int N_2 = 10000;
    double *x_2, *y_2;
    x_2 = (double *)malloc(N_2 * sizeof(double));
    y_2 = (double *)malloc(N_2 * sizeof(double));
    
    if (x_2 == NULL || y_2 == NULL) {
        perror("Errore nell'allocazione della memoria");
        return 1;
    }
    double dx_2 = (x_sup - x_inf)/N_2;
    printf("N = %d points generated in the range [%lf,%lf] with step dx=%lf.\n",N_2,x_inf,x_sup,dx_2);

    for (int i=0; i<N_2; i++){
        double x_single = i*dx_2;
        double y_single = integrand(x_single);
        x_2[i] = x_single;
        y_2[i] = y_single;
        //printf("Written x=%lf, y=%lf on file.\n",x[i],y[i]);
    }

    double I_2;
    I_2 = compute_integral(dx_2,y_2,N_2);
    printf("I_2 = %.16lf\n",I_2);
    double eps_2 = fabs(I_2/I_true - 1);
    printf("I_2 = %.16lf, I_true = %.16lf, |eps| = %.16lf considering N=%d sampling points\n",I_2,I_true,eps_2,N_2);
    free(x_2);
    free(y_2);

    // Answer question 3
    printf("The error scales as O(1/N^2).\n"); 
   
    return 0;


}
