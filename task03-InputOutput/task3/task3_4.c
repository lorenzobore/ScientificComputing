#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>

#define N 8  // Size of the vectors

void write_to_hdf5(const char* filename, const char* dataset_name, double* data, size_t size) {
    hid_t file_id, dataset_id, dataspace_id;
    hsize_t dims[1] = {size};  

    // Stampare i dati prima di scrivere nel file
    printf("Data to be written to %s:\n", dataset_name);
    for (size_t i = 0; i < size; i++) {
        printf("%lf ", data[i]);
    }
    printf("\n");

    // Create the HDF5 file
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Error creating file: %s\n", filename);
        return;
    }

    // Create the dataspace for the dataset
    dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        fprintf(stderr, "Error creating dataspace for dataset: %s\n", dataset_name);
        H5Fclose(file_id);
        return;
    }

    // Create the dataset
    dataset_id = H5Dcreate(file_id, dataset_name, H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        fprintf(stderr, "Error creating dataset: %s\n", dataset_name);
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return;
    }

    // Write the data to the dataset
    if (H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data) < 0) {
        fprintf(stderr, "Error writing data to dataset: %s\n", dataset_name);
    }

    // Close the dataset, dataspace, and file
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);
}

void read_from_hdf5(const char* filename, const char* dataset_name, double* data, size_t* size) {
    hid_t file_id, dataset_id, dataspace_id;
    hsize_t dims[1];  // Array per memorizzare le dimensioni del dataset
    herr_t status;

    // Aprire il file HDF5 (modalità sola lettura)
    file_id = H5Fopen(filename, H5F_ACC_RDONLY, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    // Aprire il dataset
    dataset_id = H5Dopen(file_id, dataset_name, H5P_DEFAULT);
    if (dataset_id < 0) {
        fprintf(stderr, "Error opening dataset: %s\n", dataset_name);
        H5Fclose(file_id);
        return;
    }

    // Ottenere lo spazio dati e le dimensioni del dataset
    dataspace_id = H5Dget_space(dataset_id);
    H5Sget_simple_extent_dims(dataspace_id, dims, NULL);
    *size = dims[0];  // Impostare la dimensione del dataset

    // Allocare memoria per i dati
    data = (double*)malloc(*size * sizeof(double));

    // Leggere i dati dal dataset
    status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    if (status < 0) {
        fprintf(stderr, "Error reading dataset: %s\n", dataset_name);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        free(data);
        return;
    }

    // Stampare i dati letti dal file HDF5
    printf("Data read from %s:\n", dataset_name);
    for (size_t i = 0; i < *size; i++) {
        printf("%lf ", data[i]);
    }
    printf("\n");

    // Chiusura delle risorse HDF5
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);
}


int main() {
    // Allocate memory for the vectors
    double* x = (double*)malloc(N * sizeof(double));
    double* y = (double*)malloc(N * sizeof(double));

    // Generate some values for x and y (simple values for demonstration)
    for (int i = 0; i < N; i++) {
        x[i] = 0.1;  
        y[i] = 7.1; 
    }


    // Write the vectors to HDF5 files
    write_to_hdf5("./data/x_data.h5", "x_dataset", x, N);
    write_to_hdf5("./data/y_data.h5", "y_dataset", y, N);

    printf("\n");

    // Free memory after writing
    free(x);
    free(y);

    // Now let's read the data back from the files
    double* x_read = (double*)malloc(N * sizeof(double));
    double* y_read = (double*)malloc(N * sizeof(double));

    size_t size_x, size_y;

    read_from_hdf5("./data/x_data.h5", "x_dataset", x_read, &size_x);
    read_from_hdf5("./data/y_data.h5", "y_dataset", y_read, &size_y);

    // Free allocated memory
    free(x_read);
    free(y_read);

    return 0;
}
