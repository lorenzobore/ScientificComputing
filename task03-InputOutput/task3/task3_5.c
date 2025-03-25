#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>
#include <gsl/gsl_vector.h>

void read_from_hdf5_to_gsl_vector(const char* filename, const char* dataset_name, gsl_vector* vec) {
    hid_t file_id, dataset_id, dataspace_id;
    hsize_t dims[1];  // Array per memorizzare la dimensione del dataset
    herr_t status;

    // Aprire il file HDF5
    file_id = H5Fopen(filename, H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Errore nell'aprire il file HDF5: %s\n", filename);
        return;
    }

    // Aprire il dataset
    dataset_id = H5Dopen(file_id, dataset_name, H5P_DEFAULT);
    if (dataset_id < 0) {
        fprintf(stderr, "Errore nell'aprire il dataset: %s\n", dataset_name);
        H5Fclose(file_id);
        return;
    }

    // Ottenere lo spazio dati del dataset
    dataspace_id = H5Dget_space(dataset_id);
    H5Sget_simple_extent_dims(dataspace_id, dims, NULL);
    
    size_t data_size = dims[0];  // Dimensione del dataset

    // Allocare memoria per il GSL vector (deve essere già allocato prima)
    if (gsl_vector_alloc(data_size) == NULL) {
        fprintf(stderr, "Errore nell'allocazione di memoria per il GSL vector!\n");
        H5Dclose(dataset_id);
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return;
    }

    // Leggere i dati dal dataset e memorizzarli nel GSL vector
    status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, gsl_vector_ptr(vec, 0));
    if (status < 0) {
        fprintf(stderr, "Errore nella lettura del dataset: %s\n", dataset_name);
        H5Dclose(dataset_id);
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return;
    }

    // Stampare i dati letti dal file HDF5
    printf("Dati letti dal dataset %s:\n", dataset_name);
    for (size_t i = 0; i < data_size; i++) {
        printf("%f ", gsl_vector_get(vec, i));
    }
    printf("\n");

    // Chiudere le risorse HDF5
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);
}

void print_vector(gsl_vector* v) {
    for (size_t i = 0; i < v->size; i++) {
        printf("v[%zu] = %f\n", i, gsl_vector_get(v, i));
    }
}

int main() {
    const char* x_filename = "./data/x_data.h5";  
    const char* y_filename = "./data/y_data.h5";  
    const char* dataset_name_x = "x_dataset";  
    const char* dataset_name_y = "y_dataset";  

    // Allocare i vettori GSL per memorizzare i dati
    size_t size = 8; 
    gsl_vector* x = gsl_vector_alloc(size);
    gsl_vector* y = gsl_vector_alloc(size);

    // Leggere i dati da HDF5 e memorizzarli nei vettori GSL
    read_from_hdf5_to_gsl_vector(x_filename, dataset_name_x, x);
    read_from_hdf5_to_gsl_vector(y_filename, dataset_name_y, y);

    // Chiamare la funzione per stampare i valori di x e y
    print_vector(x);
    printf("\n");
    print_vector(y);

    // Definisci il valore scalare 'a'
    double a = 3.0;

    // Calcola d = a * x + y usando gsl_vector_axpby
    gsl_vector_axpby(a, x, 1.0, y); 

    // Stampa il risultato
    printf("\nd vector (a * x + y) values:\n");
    print_vector(y);

    // Liberare la memoria allocata per i vettori
    gsl_vector_free(x);
    gsl_vector_free(y);

    return 0;
}
