#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

void* ptr; 

int createMemory(char * name, int SIZE)
{
    int shm_fd = -1;
    int newSize;
    shm_fd = shm_open (name, O_CREAT | O_EXCL | O_RDWR, 0600);

    if(shm_fd == -1)
    {
        printf("something went wrong in creating memory \n");
    }
    
    newSize = ftruncate(shm_fd, SIZE); 
    
    if(newSize != 0)
    {
        printf("something went wrong in truncate");
    }
    ptr = mmap (NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    return 0;
}

int  writeIntoMemory(char * name, char * message)
{
    if(name == 0)
    {
       "the file iw well maped";
    }
    sprintf(ptr, "%s", message); 
    ptr += strlen(message); 
    return 0;
}



int readFile(char * name, int SIZE)
{
    int shm_fd = -1;
    void * ptr; 
    shm_fd = shm_open (name, O_RDWR, 0600);
    ptr = mmap (NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    char * res = (char*)ptr;
    printf("result is \n ");
    
    if(res[0] == 'A')
    {
        return 0;
    }
    return -1;
} 


int readFileB(char * name, int SIZE)
{
    int shm_fd = -1;
    void * ptr; 
    shm_fd = shm_open (name, O_RDWR, 0600);
    ptr = mmap (NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    char * res = (char*)ptr;

    printf("%c \n", res[0]);
    
    if(res[0] == 'B')
    {
        return 0;
    }
    return -1;
} 

  

static void child_activities (void)
{
    /* the size (in bytes) of shared memory object */
    int SIZE = 4096; 
  
    /* name of the shared memory object */
    char* name = "OS"; 
   
    /* remove the shared memory object */
    if(readFile(name, SIZE) == 0)
    {
        // printf("delete the file \n");
        // shm_unlink(name); 
        writeA();
    }
}


void writeA()
{
    int SIZE = 4096; 
    char * name = "OS"; 
    writeIntoMemory(name, "A");
}

void writeB()
{
    int SIZE = 4096; 
    /* name of the shared memory object */
    char * name = "OS"; 
    // char message[5];
    // printf("enter a message \n");
    // scanf("%s", message);
    // printf("message is %s \n", message);
    // createMemory(name, SIZE);
    writeIntoMemory(name, "B");

}
static void parent_activity (void)
{
    /* the size (in bytes) of shared memory object */
    int SIZE = 4096; 
    /* name of the shared memory object */
    char* name = "OS"; 
    if(readFileB(name, SIZE) == 0)
    {
        writeB();
    }
 
    return NULL;
}

int main (void)
{
    /* the size (in bytes) of shared memory object */
    int SIZE = 4096; 
    /* name of the shared memory object */
    char * name = "OS"; 
    
    createMemory(name, SIZE);   
    writeA();
    pid_t   processID;      /* Process ID from fork() */
    printf ("%d main  start\n", getpid());
    
    /* creating the threads */
    processID = fork();
    if (processID < 0)
    {
        // fatal error!
        perror("fork() failed");
        exit (1);
    }

    else
    {
        if (processID == 0)
        {
            // processID == 0: child process
            child_activities();
            printf ("%d  \n", 2);
            sleep (2);
            printf ("%d  \n", 4);
            sleep (2);
            printf ("%d  \n", 6);
            sleep (2);
            printf ("%d CHILD EXIT\n", getpid());
            shm_unlink("OS"); 
            exit(0);        
            /* Child process terminates */
        }
        else
        {
            // processID > 0: main process
            parent_activity();
            printf ("%d  \n", 1);
            sleep (2);
            // writeB();
            printf ("%d  \n", 3);
            sleep (2);
            // writeB();
            printf ("%d  \n", 5);
            sleep (2);
            // writeB();
            printf ("%d main  waiting...\n", getpid());
        }
    }
    printf ("%d main  exit\n", getpid());
    return (0);
}
