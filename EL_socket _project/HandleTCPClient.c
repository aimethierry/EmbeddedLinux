#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>
#include "Auxiliary.h"
#include "HandleTCPClient.h"
#include <time.h>

#define RCVBUFSIZE 32   /* Size of receive buffer */

int sendMessageToRaspberry();
char* changeCase(char messsage[]);

void HandleTCPClient (int clntSocket)
{
    // 'clntSocket' is obtained from AcceptTCPConnection()
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int  recvMsgSize;                   /* Size of received message */
    /* Receive message from client */
    recvMsgSize = recv (clntSocket, echoBuffer,RCVBUFSIZE-1, 0);
    if (recvMsgSize < 0)
    {
        DieWithError ("recv() failed");
    }
    info_d ("Recv", recvMsgSize);

    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
        // TODO: add code to print the received string; use printf()       
        printf("%s \n",echoBuffer);
        // TODO: add code to convert the upper/lower chars of the received string
        char* message = changeCase(echoBuffer);
        /*
        printf("Prinnting modified string:");
        printf("%s\n",message);
        */
        delaying ();
        
        /* Echo message back to client */
        if (send (clntSocket, echoBuffer,recvMsgSize, 0) != recvMsgSize)
        {
            DieWithError ("send() failed");
        }
        // TODO: add code to display the transmitted string in verbose mode; use info_s()
        info_s("SERVER SENDING",message);
        // receive next string
        bzero(echoBuffer,RCVBUFSIZE);
        recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
        printf("Here:%d",recvMsgSize);
        if (recvMsgSize < 0)
        {
            DieWithError ("recv() failed");
        }
        info_d ("recv", recvMsgSize);      
        
    }
    close (clntSocket);    /* Close client socket */
    info ("close");
}

char* changeCase(char message[]){
    char s[BUFSIZ];
    int i=0;
    while(message[i] !='\0') 
     {
        if(message[i] >= 'A' && message[i] <= 'Z') {        
         message[i] += 32;
         s[i] = message[i];
        }else if(message[i]>='a' && message[i]<='z'){
           message[i] -= 32;
           s[i] = message[i];
        }
        else{
           s[i] =  message[i];
        }
        i++;
     }
    return s; 
}


int sendMessageToRaspberry()
{
    
    return 0;
}