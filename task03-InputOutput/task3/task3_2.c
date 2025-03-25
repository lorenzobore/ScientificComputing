#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_ARG_MAX_BYTES 128
#define MAX_NUMBERS 100  // Adjust based on expected data size

typedef struct config_option config_option;
typedef config_option* config_option_t;


struct config_option {
    config_option_t prev;
    char key[CONFIG_ARG_MAX_BYTES];
    char value[CONFIG_ARG_MAX_BYTES];
};

config_option_t read_config_file(char* path) {
    FILE* fp;
    
    if ((fp = fopen(path, "r+")) == NULL) {
        perror("fopen()");
        return NULL;
    }
    
    config_option_t last_co_addr = NULL;
    
    while(1) {
        config_option_t co = NULL;
        if ((co = calloc(1, sizeof(config_option))) == NULL)
            continue;
        memset(co, 0, sizeof(config_option));
        co->prev = last_co_addr;
        
        if (fscanf(fp, "%s = %s", &co->key[0], &co->value[0]) != 2) {
            if (feof(fp)) {
                break;
            }
            if (co->key[0] == '#') {
                while (fgetc(fp) != '\n') {
                    // Do nothing (to move the cursor to the end of the line).
                }
                free(co);
                continue;
            }
            perror("fscanf()");
            free(co);
            continue;
        }
        //printf("Key: %s\nValue: %s\n", co->key, co->value);
        last_co_addr = co;
    }
    return last_co_addr;
}


float* read_numbers_dynamic(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    int capacity = 10; // Initial capacity
    float* numbers = malloc(capacity * sizeof(float));
    if (!numbers) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    int count = 0;
    float num=0.0;
    while (fscanf(file, "%f", &num) == 1) {
        if (count >= capacity) {
            capacity *= 2;
            float* temp = realloc(numbers, capacity * sizeof(float));
            if (!temp) {
                perror("Memory reallocation failed");
                free(numbers);
                fclose(file);
                return NULL;
            }
            numbers = temp;
        }
        numbers[count++] = num;
    }

    fclose(file);
    *size = count;
    return numbers;
}



int main() {

    config_option_t co;

    if ((co = read_config_file("./config.cfg")) == NULL) {
        perror("read_config_file()");
        return -1;
    }

    char x_filename[128];
    char y_filename[128];
    int N;
    double a; 

    while(1) {
        char* current_key=co->key;
        char* current_value=co->value;
        printf("Current key: %s\n",current_key);
        printf("Current value: %s\n",current_value);

        if (!strcmp(current_key,"x_filename")){
            strcpy(x_filename,current_value);
            printf("Stored in x_filename as: %s\n",x_filename);
        }
        else if (!strcmp(current_key,"y_filename")){
            strcpy(y_filename,current_value);
            printf("Stored in y_filename as: %s\n",y_filename);
        }
        else if (!strcmp(current_key,"N")){
            N = atoi(co->value);
            printf("Stored in N as: %d\n",N);
        }
        else if (!strcmp(current_key,"a")){
            a = atof(co->value);
            printf("Stored in a as: %f\n",a);
        }

        printf("\n");

        if (co->prev != NULL) {
            co = co->prev;
        } else {
            break;
        }
    }

    int* size = &N;
   
    float* x = read_numbers_dynamic(x_filename, size);
    float* y = read_numbers_dynamic(y_filename, size);
    float* d = malloc(N * sizeof(float));

    for (int i=0;i<N;i++){
        d[i] = a*x[i]+y[i];
        printf("%d => a=%f, x=%f, y=%f => d=%f\n",i,a,x[i],y[i],d[i]);
    }
    printf("\n");

    // Open file and write values on it
    FILE *fp_out = fopen("./d_output.dat", "w");
    if (fp_out != NULL){
        for (int i=0; i<N; i++){
            char format[16]="%f\n";
            float value=d[i];
            fprintf(fp_out, format, value);
        }
    }
    else{
        printf("ERROR: file %s did not open!","./d_output.dat");
    }
    int fclose(FILE *fp_out);

    return 0;
}
