f=*.c
objs=*.o
exe=prog
CC=gcc
FLAGS=
DEBUG=-g

$(exe): $(objs) $f
	$(CC) $(objs) -o prog $(FLAGS) $(DEBUG)

$(objs): $f
	$(CC) -c $f $(FLAGS) $(DEBUG)

clean:
	rm $(objs)

clr:
	rm $(objs) $(exe)
