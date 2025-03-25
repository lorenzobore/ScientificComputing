# Task3 - Readme
Codes are also available at: https://github.com/lorenzobore/ScientificComputing

### Content of folder `task3`:
* **CONFIG FILE**(`config.cfg`): file used to read N=8, a=3.0, x_filename e y_filename.

* **SOURCES**(`task3_1.c`,`task3_2.c`,`task3_4.c`,`task3_5.c`): source files for the different points required by the task.

* **DATA FOLDER**(`data`): folder containing:
    * `vector_N8_x.dat` e `vector_N8_y.dat` generated with `task3_1.c`
    * `d_output.dat` the output values computed in `task3_1.c`
    * `x_data.h5` e `y_data.h5` produced in `task3_4.c`
* **Makefile**: to organize compilation.
    ```
    CC = gcc
    CFLAGS = -Wall -Wextra -g

    # Source files
    SRC1 = task3_1.c
    SRC2 = task3_2.c
    SRC3 = task3_4.c
    SRC4 = task3_5.c

    # Output executables
    OUT1 = task3_1.exe
    OUT2 = task3_2.exe
    OUT3 = task3_4.exe
    OUT4 = task3_5.exe

    all: $(OUT1) $(OUT2) $(OUT3) $(OUT4)

    $(OUT1): $(SRC1)
        $(CC) $(CFLAGS) -o $(OUT1) $(SRC1)

    $(OUT2): $(SRC2)
        $(CC) $(CFLAGS) -o $(OUT2) $(SRC2) 

    $(OUT3): $(SRC3)
        $(CC) $(CFLAGS) -o $(OUT3) $(SRC3) -lhdf5 

    $(OUT4): $(SRC4)
        $(CC) $(CFLAGS) -o $(OUT4) $(SRC4) -lhdf5 -lgsl -lgslcblas -lm

    clean:
        rm -f $(OUT1) $(OUT2) $(OUT3) $(OUT4)
    ```


### How to run the codes:
1. Type `make` to compile all the `.c` files and overwrite the executables.

2. Run `./task3_1.exe` to execute the first point of task 3. You will be asked to provide:
    * The length of input vectors, insert `8`.
    * The data folder, insert `./data/`.

    Eventually the x and y data files will be generated.
    ```
    Insert length of vectors N:
    8
    Value inserted: N=8
    --------------------

    Insert folder:
    ./data/
    Value inserted for folder: ./data/
    --------------------

    Written File for x: ./data/vector_N8_x.dat
    Written File for y: ./data/vector_N8_y.dat

    --------------------

    ```

3. Run `./task_3.2.exe` to perform the second point of task2. The `config.cfg` file looks as follows:

    ```
    # Configuration  file
    x_filename = ./data/vector_N8_x.dat
    y_filename = ./data/vector_N8_y.dat
    N = 8
    a = 3.0
    ```

    This file is read and its contents are stored in global variables, then vectors are generated and saved to file, as you can see from the output:

    ```
    Current key: a
    Current value: 3.0
    Stored in a as: 3.000000

    Current key: N
    Current value: 8
    Stored in N as: 8

    Current key: y_filename
    Current value: ./data/vector_N8_y.dat
    Stored in y_filename as: ./data/vector_N8_y.dat

    Current key: x_filename
    Current value: ./data/vector_N8_x.dat
    Stored in x_filename as: ./data/vector_N8_x.dat

    0 => a=3.000000, x=0.100000, y=7.100000 => d=7.400000
    1 => a=3.000000, x=0.100000, y=7.100000 => d=7.400000
    2 => a=3.000000, x=0.100000, y=7.100000 => d=7.400000
    3 => a=3.000000, x=0.100000, y=7.100000 => d=7.400000
    4 => a=3.000000, x=0.100000, y=7.100000 => d=7.400000
    5 => a=3.000000, x=0.100000, y=7.100000 => d=7.400000
    6 => a=3.000000, x=0.100000, y=7.100000 => d=7.400000
    7 => a=3.000000, x=0.100000, y=7.100000 => d=7.400000
    ```

3. `./task3_4.exe` writes the `.h5` files with the content of the arrays x and y. Then they are read back to debug.
    ```
    Data to be written to x_dataset:
    0.100000 0.100000 0.100000 0.100000 0.100000 0.100000 0.100000 0.100000 
    Data to be written to y_dataset:
    7.100000 7.100000 7.100000 7.100000 7.100000 7.100000 7.100000 7.100000 

    Data read from x_dataset:
    0.100000 0.100000 0.100000 0.100000 0.100000 0.100000 0.100000 0.100000 
    Data read from y_dataset:
    7.100000 7.100000 7.100000 7.100000 7.100000 7.100000 7.100000 7.100000 
    ```

4. Run `./task3_5.exe` to read the `.h5` files and perform the $d=a*x+y$ operation using `gsl_vector_axpby`.

    ```
    Dati letti dal dataset x_dataset:
    0.100000 0.100000 0.100000 0.100000 0.100000 0.100000 0.100000 0.100000 
    Dati letti dal dataset y_dataset:
    7.100000 7.100000 7.100000 7.100000 7.100000 7.100000 7.100000 7.100000 
    v[0] = 0.100000
    v[1] = 0.100000
    v[2] = 0.100000
    v[3] = 0.100000
    v[4] = 0.100000
    v[5] = 0.100000
    v[6] = 0.100000
    v[7] = 0.100000

    v[0] = 7.100000
    v[1] = 7.100000
    v[2] = 7.100000
    v[3] = 7.100000
    v[4] = 7.100000
    v[5] = 7.100000
    v[6] = 7.100000
    v[7] = 7.100000

    d vector (a * x + y) values:
    v[0] = 7.400000
    v[1] = 7.400000
    v[2] = 7.400000
    v[3] = 7.400000
    v[4] = 7.400000
    v[5] = 7.400000
    v[6] = 7.400000
    v[7] = 7.400000
    ```

Eventually you can type `make clean` to remove all the executables from the folder.
