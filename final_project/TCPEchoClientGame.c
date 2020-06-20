#include <stdio.h>
#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include "Auxiliary.h"
#include "CreateTCPClientSocket.h"
// #include "game.h"
#define RCVBUFSIZE 32   /* Size of receive buffer */



int main (int argc, char *argv[])
{
    int         sock;                   /* Socket descriptor */
    char *      echoString;             /* String to send to echo server */
    char        echoBuffer[RCVBUFSIZE]; /* Buffer for received string */
    int         echoStringLen;          /* Length of string to echo */
    int         bytesRcvd;              /* Bytes read in single recv() */
    //int         i;                      /* counter for data-arguments */
    parse_args (argc, argv);
    sock =CreateTCPClientSocket(argv_ip, argv_port);  
    char sendBuffer[32];    

    printf("please enter q or quit to close \n \n \n");
    
    while(1)
    {	
        printf("enter a message \n");
		scanf("%s", sendBuffer);
		printf("sender message is %s \n \n", sendBuffer);
        int send_val = strlen(sendBuffer);
        printf("size of my string is %d \n \n", send_val);
		// TODO: add code to send this string to the server; use send()
        send(sock,sendBuffer, send_val + 1, 0);
        // TODO: add code to display the transmitted string in verbose mode; use 
        info_s(sendBuffer, sendBuffer);
        // TODO: add code to receive & display the converted string from the server
        //       use recv() & printf()
        bytesRcvd =recv(sock, echoBuffer, RCVBUFSIZE-1, 0);
        //check if there is something received 
        if(bytesRcvd < 0)
        {
			printf("there was an error in receiving \n");
		}
		else
		{
			printf("received data are: %s \n", echoBuffer);
            //quit when the value is quit 
			
            int rescmp = strcmp(echoBuffer, "Q");
        
            int resplay = strcmp(echoBuffer, "P");
            
            if((resplay == 0))
            {
                printf("am done playing the snake game \n");
                //  startPlayGameSnakeGame();
            }

			if((rescmp == 0))
			{
				close(sock); //close the client 
                info("close & exit");
                exit(0);
			}

           
			//set the buffer to zero 
            bzero(echoBuffer,sizeof(echoBuffer));
		}
        //close the buffer when the receive length of data is zero 
	
    }

    
    return 0;
}



