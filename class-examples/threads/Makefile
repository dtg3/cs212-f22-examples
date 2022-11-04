
FLAGS = -Wall -pthread

all: t0 t1 t2

clean:
	rm -f t0 t1 t2

t0: t0-fixed.c
	gcc -o t0 t0-fixed.c $(FLAGS)

t1: t1-fixed.c
	gcc -o t1 t1-fixed.c $(FLAGS)

t2: t2-fixed.c
	gcc -o t2 t2-fixed.c $(FLAGS)
