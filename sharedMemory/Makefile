# make file for shared memory

CC = gcc
LDFLAGS = -lrt


.PHONY: all clean

all:shmw shmr

shmw:shmw.o 
	gcc -o shmw shmw.o -lrt 

shmr:shmr.o
	gcc -o shmr shmr.o -lrt

shmw.o:shmwrite.c shmwrite.h
	gcc -c -o  shmw.o shmwrite.c

shmr.o: shmread.c shmread.h
	gcc -c -o  shmr.o shmread.c

clean:
	rm -rf shmr shmw shared