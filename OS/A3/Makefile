# The Makefile creates seperate executables for each .c file
#	The executables are created with the .exe suffix
SOURCES = $(wildcard *.c)
EXECUTABLES = $(SOURCES:.c=.exe)
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Werror

all: $(EXECUTABLES)

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLES)
