# Compiler and flags
CC = gcc

# Files
LEX = airport.lex
LEX_GEN = lex.yy.c

HDR = airport.h
SRC = airport.c
OBJ = $(SRC:.c=.o)

EXE = airport

# Default rule
all: $(EXE)

# Build the executable
$(EXE): $(LEX_GEN) $(OBJ)
	$(CC) -o $@ $^

# Generate lex.yy.c from Flex
$(LEX_GEN): $(LEX)
	flex $(LEX)

# Clean rule
clean:
	rm -f $(EXE) $(LEX_GEN) $(OBJ)
