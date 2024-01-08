f=*.c
obj=*.o
exe=prog
CC=gcc
FLAGS=

$(exe): $(obj) $f
	$(CC) $(FLAGS) $(obj) -o prog

$(obj): $f
	$(CC) -c $f

clean:
	rm $(obj)

clr:
	rm $(obj) $exe
