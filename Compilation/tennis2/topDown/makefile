CC = gcc
objects = tennis.o lex.yy.o  

tennis: $(objects)
	$(CC) -o tennis $(objects)


lex.yy.o : lex.yy.c tennis.h
	$(CC) -c lex.yy.c

tennis.o : tennis.c tennis.h 
	$(CC) -c tennis.c
	
lex.yy.c : tennis.lex
	flex tennis.lex
	
clean :
	rm -f $(objects) tennis  lex.yy.c
