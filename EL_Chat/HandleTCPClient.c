#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>
#include "Auxiliary.h"
#include "HandleTCPClient.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */
char* changeCase(char messsage[]);

void HandleTCPClient (int clntSocket)
{
    // 'clntSocket' is obtained from AcceptTCPConnection()
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int  recvMsgSize;                   /* Size of received message */

    /* Receive message from client */
    recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
    if (recvMsgSize < 0)
    {
        DieWithError ("recv() failed");
    }
    info_d ("Recv", recvMsgSize);
	
	
	/* Send received string and receive again until end of transmission */
	while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {

		int str_val = 0;		
		printf("%s \n",echoBuffer);
		//get the length of data to send 
		str_val = strlen(echoBuffer);
		//printing the length of our values 
		printf("size of the length is %d \n", str_val);

	
		//sending value state 
		//start sending the values 
		send(clntSocket,echoBuffer, str_val + 1, 0);

		//print the sending message 
		printf("sending message %s \n", echoBuffer);

		//clear the buffer 
		bzero(echoBuffer,str_val);
		
		//get the next value in the buffer
		printf("check of other values \n");
		recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
		if (recvMsgSize < 0)
		{
			DieWithError ("recv() failed");
		}
	}
}

