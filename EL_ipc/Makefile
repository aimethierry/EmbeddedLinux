CC=gcc



.PHONY: all clean

all:Thread fork ncruses game

game:game.o 
	gcc -o game game.o -lncurses

game.o:game.c
	gcc -c -o game.o game.c 

Thread: Thread.o 
	gcc -o Thread Thread.o -lpthread

ncruses:ncruses.o
	gcc -o ncruses ncruses.o -lncurses

ncruses.o:ncruses.c
	gcc -c -o ncruses.o ncruses.c 

fork:fork.o 
	gcc -o fork fork.o -lrt

fork.o:fork.c
	gcc -c -o fork.o fork.c 



Thread.o:thread.c 
	gcc -c -o Thread.o thread.c

clean:
	rm -rf Thread Thread.o \
	fork fork.o