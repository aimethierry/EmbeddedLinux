#include <pthread.h>
#include "Auxiliary.h"
#include "AcceptTCPConnection.h"
#include "CreateTCPServerSocket.h"
#include "HandleTCPClient.h"

static void * myThread (void * arg);            /* thread that does the work */

int main (int argc, char *argv[])
{
    int         servSock;     /* Socket descriptor for server */
    int         clntSock;     /* Socket descriptor for client */
    pthread_t   threadID;     /* Thread ID from pthread_create() */
    bool        to_quit = false;

    parse_args (argc, argv);
    servSock = CreateTCPServerSocket (argv_port);
    while (to_quit == false)                /* run until someone indicates to quit... */
    {

        clntSock = AcceptTCPConnection (servSock);
        pthread_t   thread_a;
        
        printf("sock is %d \n \n", clntSock);
        int * ptr; 
        ptr[0] = clntSock ;
        ptr[1] = 3000;
        if (pthread_create (&thread_a, NULL, myThread, (void *) ptr)!= 0)
        {
            perror ("pthread_create(a)");
        }
        printf(" \n \n thread is starting and the thread id is %ld \\n \n \n", thread_a);
        pthread_join(thread_a, NULL);
    }
    
    // server stops...
	return (0);
}


static void *
myThread (void * threadArgs)
{
    // TODO: write the code to handle the client data
    // use operation HandleTCPClient()
    int clnsock;
    clnsock =  * ((int *) (threadArgs) );
    // clnsock  = *((int *) (threadArgs + 1));
    printf("my client sock is %d \n", clnsock);
    HandleTCPClient(threadArgs);
    
    // Hint: use the info(), info_d(), info_s() operations to trace what happens
    //
    // Note: a call of pthread_detach() is obligatory

    return (NULL);
}
