objects = madonna.o lex.yy.o  

madonna.exe: $(objects)
	gcc -o madonna.exe $(objects)


lex.yy.o : lex.yy.c madonna.h
	gcc -c lex.yy.c

madonna.o : madonna.c madonna.h 
	gcc -c madonna.c
	
lex.yy.c : madonna.lex
	flex madonna.lex
	
clean :
	rm $(objects) madonna.exe


	


