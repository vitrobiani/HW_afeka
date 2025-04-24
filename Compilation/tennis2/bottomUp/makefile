CC = gcc

OBJECTS = lex.yy.o tennis.tab.o

tennis: $(OBJECTS)
	$(CC) $(OBJECTS)  -o tennis


lex.yy.c: tennis.lex
	flex tennis.lex
	
tennis.tab.c tennis.tab.h: tennis.y
	bison -d tennis.y
	
lex.yy.o: lex.yy.c tennis.tab.h

tennis.tab.o: tennis.tab.c

clean:
	rm -f tennis tennis.tab.c tennis.tab.h lex.yy.c $(OBJECTS)
	
	