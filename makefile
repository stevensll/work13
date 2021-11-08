all: main.o
	gcc -o reader.out main.o functions.o
main.o: main.c functions.c functions.h
	gcc -c main.c functions.c
functions.o: functions.c functions.h
	gcc -c functions.c

run:
	./reader.out
