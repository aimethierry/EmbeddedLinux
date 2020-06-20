CC=gcc



.PHONY: all clean

all:Thread fork ncruses game signal  sem  async game2


async:async.o
	gcc -o async async.o -lpthread

async.o:async.c 
	gcc -c -o async.o async.c 


sem:sem.o
	gcc -o sem sem.o -lpthread

sem.o:sem.c 
	gcc -c -o sem.o sem.c 



signal:signal.o
	gcc -o signal signal.o -lrt

signal.o:signal.c 
	gcc -c -o signal.o signal.c



game:game.o 
	gcc -o game game.o -lncurses -lrt -lpthread

game2:game2.o 
	gcc -o game2 game2.o -lncurses -lrt -lpthread

game.o:game.c
	gcc -c -o game.o game.c 

game2.o:game2.c
	gcc -c -o game2.o game2.c 

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
	fork fork.o \
	signal signal.o sem..o sem rendezvous.o rendezvous game game.o ncruses async async.o \
	game2 game2.o
