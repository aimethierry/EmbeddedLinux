
// C program for Consumer process illustrating 
// POSIX shared-memory API. 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include "shmread.h"

int readFile(char * name, int SIZE)
{
    int shm_fd = -1;
    void * ptr; 
    shm_fd = shm_open (name, O_RDWR, 0600);
    ptr = mmap (NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    char * res = (char*)ptr;
    printf("%c \n", res[0]);
    
    if(res[0] == 'A')
    {
        return success;
    }
    return fail;
} 

  
int main()
{ 
    /* the size (in bytes) of shared memory object */
    int SIZE = 4096; 
  
    /* name of the shared memory object */
    char* name = "OS"; 
   
    /* remove the shared memory object */
    if(readFile(name, SIZE) == success)
    {
        printf("delete the file \n");
        shm_unlink(name); 
        return success;
    }
    return fail; 
} 
