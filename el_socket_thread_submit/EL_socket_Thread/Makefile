CC=gcc
FLAGS=-Wall

.PHONY:all clean 

all:  TCPEchoClient TCPEchoServerThread

TCPEchoClient:TCPEchoClient.o Auxiliary.o CreateTCPClientSocket.o
	gcc -o TCPEchoClient TCPEchoClient.o Auxiliary.o CreateTCPClientSocket.o -lrt 


#include "Auxiliary.h"
#include "AcceptTCPConnection.h"
#include "CreateTCPServerSocket.h"
#include "HandleTCPClient.h"

TCPEchoServerThread:TCPEchoServerThread.o  Auxiliary.o AcceptTCPConnection.o CreateTCPServerSocket.o HandleTCPClient.o TCPEchoServer.o
	gcc -o TCPEchoServerThread Auxiliary.o AcceptTCPConnection.o CreateTCPServerSocket.o HandleTCPClient.o TCPEchoServer.o  -lrt -lpthread  


TCPEchoServerThread.o:TCPEchoServer-Thread.c AcceptTCPConnection.h CreateTCPServerSocket.h HandleTCPClient.h
	gcc -c -o TCPEchoServerThread.o TCPEchoServer-Thread.c


AcceptTCPConnection.o:AcceptTCPConnection.c Auxiliary.h
	$(CC) $(FLAGS) -c -o AcceptTCPConnection.o  AcceptTCPConnection.c

CreateTCPServerSocket.o:CreateTCPServerSocket.h Auxiliary.h
	$(CC) $(FLAGS) -c -o CreateTCPServerSocket.o  CreateTCPServerSocket.c


	
HandleTCPClient.o:HandleTCPClient.c Auxiliary.h HandleTCPClient.h
	$(CC) $(FLAGS) -c -o HandleTCPClient.o  HandleTCPClient.c -lpthread


TCPEchoClient.o:TCPEchoClient.c Auxiliary.h CreateTCPClientSocket.h
	$(CC) $(FLAGS) -c -o TCPEchoClient.o  TCPEchoClient.c

Auxiliary.o:Auxiliary.c Auxiliary.h
	$(CC) $(FLAGS) -c -o Auxiliary.o  Auxiliary.c

CreateTCPClientSocket.o:CreateTCPClientSocket.c	Auxiliary.h	CreateTCPClientSocket.h
	$(CC) $(FLAGS) -c -o CreateTCPClientSocket.o  CreateTCPClientSocket.c 

clean:
	rm -rf  AcceptTCPConnection.o Auxiliary.o CreateTCPClientSocket.o \
	AcceptTCPConnection.o CreateTCPServerSocket.o getaddrinfo.o \
	 HandleTCPClient.o TCPEchoClient.o TCPEchoServer-Fork.o \
	 TCPEchoServer.o TCPEchoServer-Thread.o TCPEchoClient \
	  TCPEchoServer-Fork TCPEchoServer TCPEchoServer-Thread \
	  TCPEchoServerThread TCPEchoServerThread.o