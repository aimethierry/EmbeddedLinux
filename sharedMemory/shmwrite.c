#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>


#include "shmwrite.h"

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
    return success;
}

int  writeIntoMemory(char * name, char * message)
{
    if(name == success)
    {
       "the file iw well maped";
    }
    sprintf(ptr, "%s", message); 
    ptr += strlen(message); 
    return success;
}
  
int main() 
{ 
    /* the size (in bytes) of shared memory object */
    int SIZE = 4096; 
  
    /* name of the shared memory object */
    char * name = "OS"; 

    char message[5];

    printf("enter a message \n");
    scanf("%s", message);

    createMemory(name, SIZE);
    writeIntoMemory(name, "A");
    return 0; 
} 