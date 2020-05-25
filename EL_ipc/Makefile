CC=gcc



.PHONY: all clean

all:Thread fork 

Thread: Thread.o 
	gcc -o Thread Thread.o -lpthread

fork:fork.o 
	gcc -o fork fork.o -lrt

fork.o:fork.c
	gcc -c -o fork.o fork.c 


Thread.o:thread.c 
	gcc -c -o Thread.o thread.c

clean:
	rm -rf Thread Thread.o \
	fork fork.o