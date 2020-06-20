#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include "Auxiliary.h"
#include "CreateTCPClientSocket.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */



int main (int argc, char *argv[])
{
    int         sock;                   /* Socket descriptor */
    char *      echoString;             /* String to send to echo server */
    char        echoBuffer[RCVBUFSIZE]; /* Buffer for received string */
    int         echoStringLen;          /* Length of string to echo */
    int         bytesRcvd;              /* Bytes read in single recv() */
    int         i;                      /* counter for data-arguments */
    parse_args (argc, argv);
    sock = CreateTCPClientSocket (argv_ip, argv_port);
    i = 0;
    while(1)
    {

        send(sock,"hello world",12, 0);
        // TODO: add code to receive & display the converted string from the server
        //       use recv() & printf()
        bzero(echoBuffer,sizeof(echoBuffer));
        bytesRcvd = recv (sock, echoBuffer,sizeof(echoBuffer), 0);
        if(bytesRcvd < 0){
            DieWithError ("recv() failed");
        }
        
        printf("Receiving:%s \n",echoBuffer);

        if(echoBuffer[0] == 'T')
        {
            printf("go to arduiono \n");
            char * message = "echo 'T'>/dev/ttyUSB0";
            printf("%s", message);
            system(message);
            
        }

        bzero(echoString,echoStringLen);
    }
    close (sock);
    info (" \n close & exit");
    exit (0); 
    return 0;
}