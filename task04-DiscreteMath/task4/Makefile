CC = gcc
CFLAGS = -Wall -Wextra -g

# Source files
SRC = task4.c

# Output executables
OUT = task4.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) -lm

clean:
	rm -f $(OUT) 