#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>
#include "Auxiliary.h"
#include "HandleTCPClient.h"
#include <time.h>
#include <time.h>
#include <string.h>

#define RCVBUFSIZE 32   /* Size of receive buffer */

int sendMessageToRaspberry();
char* changeCase(char messsage[]);
char openGate[2];
int  openOnce = 0;

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


    while(1)
    {
        if(sendMessageToRaspberry() == 0)
        {    
            send (clntSocket, "T", recvMsgSize, 0);   
        }
        send (clntSocket, "F", recvMsgSize, 0);   
    }
}



int sendMessageToRaspberry()
{
  time_t current_time;
  struct tm * time_info;
  char timeString[9];  // space for "HH:MM:SS\0"

  time(&current_time);
  time_info = localtime(&current_time);

  strftime(timeString, sizeof(timeString), "%H:%M", time_info);
  puts(timeString);
  int res = strcmp(timeString, "14:20");
  int res2 = strcmp(timeString, "7:00");
  int res3 = strcmp(timeString, "19:34");
  
//   if(res == 0 || res2 == 0 || res3 == 0)
//   {
//     printf("time is  time to open %s \n", timeString);
//     return 0;
//   }

  printf("Enter T To open gate \n");
  scanf("%s", openGate);

  printf("entered character is %c \n", openGate[0]);

  int resOpenGatevalue = strcmp(openGate, "T");
  printf("res is  %d \n", resOpenGatevalue);

  if(resOpenGatevalue == 0)
  {
    printf("time is  time to open %s \n", timeString);
    return 0;
  }
  return -1;
}