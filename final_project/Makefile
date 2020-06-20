CC=gcc
FLAGS=-Wall

.PHONY:all clean 

all: TCPEchoClientGame tryplaying  TCPEchoServer-Thread

# TCPEchoServer
# TCPEchoServer-Thread TCPEchoClient

tryplaying:tryplaying.o newGame.o
	gcc -o tryplaying tryplaying.o newGame.o -lncurses -lrt -lpthread


tryplaying.o:tryplaying.c newGame.h
	gcc -c -o tryplaying.o tryplaying.c 



newGame.o:newGame.c newGame.h
	gcc -c -o newGame.o newGame.c 



TCPEchoServer-Thread:TCPEchoServer-Thread.o  Auxiliary.o game.o newGame.o AcceptTCPConnection.o CreateTCPServerSocket.o HandleTCPClient.o 
	gcc -o TCPEchoServer-Thread Auxiliary.o AcceptTCPConnection.o game.o newGame.o CreateTCPServerSocket.o HandleTCPClient.o TCPEchoServer-Thread.o -lrt -lpthread -lncurses 


TCPEchoClientGame:TCPEchoClientGame.o  Auxiliary.o CreateTCPClientSocket.o
	gcc -o TCPEchoClientGame TCPEchoClientGame.o   Auxiliary.o CreateTCPClientSocket.o -lncurses -lrt -lpthread

game.o:game.c game.h
	gcc -c -o game.o game.c 

# -lncurses -lrt -lpthread


TCPEchoClientGame.o:TCPEchoClientGame.c Auxiliary.h CreateTCPClientSocket.h 
	gcc -c -o TCPEchoClientGame.o TCPEchoClientGame.c



TCPEchoServer-Thread.o: TCPEchoServer-Thread.c AcceptTCPConnection.h CreateTCPServerSocket.h HandleTCPClient.h
	$(CC) $(FLAGS) -c -o TCPEchoServer-Thread.o  TCPEchoServer-Thread.c


AcceptTCPConnection.o:AcceptTCPConnection.c Auxiliary.h
	$(CC) $(FLAGS) -c -o AcceptTCPConnection.o  AcceptTCPConnection.c

CreateTCPServerSocket.o:CreateTCPServerSocket.h Auxiliary.h
	$(CC) $(FLAGS) -c -o CreateTCPServerSocket.o  CreateTCPServerSocket.c


TCPEchoClient:TCPEchoClient.o Auxiliary.o CreateTCPClientSocket.o 
	gcc -o TCPEchoClient TCPEchoClient.o Auxiliary.o CreateTCPClientSocket.o -lrt -lncurses -lpthread


HandleTCPClient.o:HandleTCPClient.c Auxiliary.h HandleTCPClient.h game.h newGame.h
	$(CC) $(FLAGS) -c -o HandleTCPClient.o  HandleTCPClient.c


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
	  TCPEchoServer-Fork TCPEchoServer TCPEchoServer-Thread game.o game \
	  tryplaying.o tryplaying TCPEchoClientGame