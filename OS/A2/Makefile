# List of source files
SOURCES = $(wildcard *.c)

# Derive the executable names by removing the .c suffix and adding .exe
EXECUTABLES = $(SOURCES:.c=.exe)

# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2

# Default target: build all executables
all: $(EXECUTABLES)

# Rule to build each executable
%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean up generated files
clean:
	rm -f $(EXECUTABLES)
