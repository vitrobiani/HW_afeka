LEX     = airport.lex
YACC    = airport.y
TARGET  = airport

# Generated
LEX_C   = lex.yy.c
YACC_C  = airport.tab.c
YACC_H  = airport.tab.h

# Compiler
CC      = gcc

# Default rule
all: $(TARGET)

$(TARGET): $(LEX_C) $(YACC_C)
	$(CC) -o $@ $(LEX_C) $(YACC_C)

$(LEX_C): $(LEX)
	flex $(LEX)

$(YACC_C) $(YACC_H): $(YACC)
	bison -d $(YACC)

clean:
	rm -f $(TARGET) $(LEX_C) $(YACC_C) $(YACC_H)
