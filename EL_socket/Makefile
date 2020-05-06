CC=gcc
FLAGS=-Wall

.PHONY:all clean 

all: TCPEchoClient 

TCPEchoClient:TCPEchoClient.o Auxiliary.o CreateTCPClientSocket.o
	gcc -o TCPEchoClient TCPEchoClient.o Auxiliary.o CreateTCPClientSocket.o -lrt 


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
	  TCPEchoServer-Fork TCPEchoServer TCPEchoServer-Thread