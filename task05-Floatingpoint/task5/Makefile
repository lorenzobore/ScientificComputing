CC = gcc
CFLAGS = -Wall -Wextra -g

# Source files
SRC = task5.c

# Output executables
OUT = task5.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) -lhdf5 -lgsl -lgslcblas -lm

clean:
	rm -f $(OUT) 