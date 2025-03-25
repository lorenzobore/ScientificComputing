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