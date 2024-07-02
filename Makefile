# Makefile for the GCC project
CC=gcc
CFLAGS=-g -I.
LDFLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wno-builtin-declaration-mismatch
SRC_DIR=src
EXE=bin/game

# Find all .c files in the src directory and its subdirectories
SRCS=$(shell find $(SRC_DIR) -type f -name '*.c')


all:
	$(CC) $(CFLAGS) $(SRCS) -o ${EXE} $(LDFLAGS)

# Clean up
clean:
	rm -rf bin

# Compile and run the executable
run: all
	./$(EXE)

# Run the executable only if it exists
single:
	@if [ -f $(EXE) ]; then \
		./$(EXE); \
	else \
		echo "Executable not found. Run 'make' to compile first."; \
	fi

.PHONY: all clean run single
