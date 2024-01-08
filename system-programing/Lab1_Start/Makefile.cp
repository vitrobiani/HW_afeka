obj =  main.o functionsLab1.o
exe = prog


$(exe): $(obj)
	gcc main.o functionsLab1.o -o prog

main.o:
	gcc -c main.c

functionsLab1.o:
	gcc -c functionsLab1.c

clean:
	rm main.o functionsLab1.o prog
