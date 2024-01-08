obj = prog.o arrays.o functionsLab2.o exe.o
exe = prog

$(exe): $(obj)
	gcc $(obj) -o prog

${obj[0]}:
	gcc -c prog.c

${obj[1]}:
	gcc -c arrays.c

functionsLab.o:
	gcc -c functionsLab2.c

exe.o:
	gcc -c exe.c

clr:
	rm *.o

clean:
	rm $(obj) $(exe)

