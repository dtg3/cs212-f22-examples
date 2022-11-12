FLAGS = -Wall -pthread

driver: main

clean:
	rm -f main *.o

couting-scaling.o: counting-scaling.c counting-scaling.h
	gcc -c counting-scaling.c $(FLAGS)

main.o: main.c counting-scaling.h
	gcc -c main.c $(FLAGS)

main: main.o couting-scaling.o
	gcc -o main main.o counting-scaling.o $(FLAGS)

	

