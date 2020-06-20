#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include "Auxiliary.h"
#include "AcceptTCPConnection.h"
#include "CreateTCPServerSocket.h"
#include "HandleTCPClient.h"

static void * myThread (void * arg);            /* thread that does the work */


struct arg_struct{
    int clntSock;
    int number;
};



int main (int argc, char *argv[])
{
    int         servSock;     /* Socket descriptor for server */
    int         clntSock;     /* Socket descriptor for client */
    pthread_t   threadID;     /* Thread ID from pthread_create() */
    bool        to_quit = false;

     
    struct arg_struct p_data;

    

    parse_args (argc, argv);

    servSock = CreateTCPServerSocket (argv_port);

    while (to_quit == false)                /* run until someone indicates to quit... */
    {
        clntSock = AcceptTCPConnection (servSock);
        pthread_t   thread_a;
        printf("sock is %d \n \n", clntSock);
        int * ptr;

       
        p_data.clntSock = clntSock;
        p_data.number = 300;
        
        if (pthread_create (&thread_a, NULL, myThread, (void *) &p_data)!= 0)
        {
            perror ("pthread_create(a)");
        }

        // printf(" \n \n thread is starting and the thread id is %ld \\n \n \n", thread_a);
        // pthread_join(thread_a, NULL);
    }
    
    close (servSock);
    info ("close");
    // server stops...
	return (0);
}


static void *
myThread (void * threadArgs)
{
    // TODO: write the code to handle the client data
    // use operation HandleTCPClient()
    struct arg_struct *args = (struct arg_struct *)threadArgs;
    int clnsock;
    sem_t* semController;
    clnsock = (int)args->clntSock;
    char semCName[] = "Aime";
    semController = sem_open(semCName, O_CREAT | O_EXCL, 0600, 1); 
    printf("my client sock is %d  and my id is %d \n", clnsock, getpid());
    HandleTCPClient(clnsock, semController);
    if (pthread_detach (pthread_self ()) != 0)
    {
        perror ("pthread_detach(b)");
    }
    return (NULL);
}
