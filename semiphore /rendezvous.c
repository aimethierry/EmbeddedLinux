// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// #include <errno.h>
// #include <semaphore.h>
// #include <sys/types.h>
// #include <sys/mman.h>
// #include <sys/stat.h>
// #include <sys/fcntl.h>
// #include <stdlib.h>


// sem_t *  semP  = SEM_FAILED;
// sem_t*   semGo = SEM_FAILED;
// int      shm_fd = -1;
// char semPName[] = "semPName";
// char semGoName[] = "semGo";
// char shmName[]= "lock_count";

// void printStatementOne();
// void printStatementTwo();
// void runParallel();
// void printValue();
// void close_shm(char* shm_addr,char * shm_name);



// static char *my_shm_create (char * shm_name, int size);


// void runParallel(char* shm_addr){
//     sem_wait(semP);
//     printStatementOne(); 
//     *shm_addr +=1;
//     printValue(shm_addr);
//     sem_post(semP);
//     if(*shm_addr =='4'){
        
//         sem_post(semGo);
//         sem_post(semGo); 
//         sem_post(semGo); 
//         sem_post(semGo);                     
//     }
//     sem_wait(semGo);
//     *shm_addr +=1;
//     printValue(shm_addr);
//     printStatementTwo(); 
//     close_shm(shm_addr,shmName);    
// }
// void close_shm(char* shm_addr,char * shm_name){
//      int rtn; 
//      if(*shm_addr == '8'){
//         printf("------Closing all-------");
//         rtn = close (shm_fd);
//         if (rtn != 0)
//         {
//             perror ("ERROR: close() failed");
//         }
//         printf ("close() returned %d\n", rtn);
//         shm_fd = -1;
//         rtn = shm_unlink(shmName);
//         if (rtn != 0)
//         {
//             perror ("ERROR: shm_unlink() failed");
//         }
//         printf ("shm_unlink() returned %d\n", rtn);
//     }  
// }
// void printStatementOne(){
//     printf("PID:%d \t Statement 1\n",getpid());
// }
// void printStatementTwo(){
//     printf("PID:%d \t Statement 2\n",getpid());
// }
// static char *
// my_shm_open (char * shm_name)
// {
//     int     size;
//     char *  shm;
//     shm_fd = shm_open (shm_name, O_RDWR, 0600);
//     if (shm_fd == -1)
//     {
//         perror ("ERROR: shm_open() failed");
//     }
//     size = lseek (shm_fd, 0, SEEK_END);
//     shm = (char *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
//     if (shm == MAP_FAILED)
//     {
//         perror ("ERROR: mmap() failed");
//     }
//     return (shm);
// }
// static char *
// my_shm_create (char * shm_name, int size)
// {
//     int     rtnval;
//     char *  shm;
    
//     shm_fd = shm_open (shm_name, O_CREAT | O_EXCL | O_RDWR, 0600);
//     if (shm_fd == -1)
//     {
//         perror ("ERROR: shm_open() failed");
//     }

//     rtnval = ftruncate (shm_fd, size);
//     if (rtnval != 0)
//     {
//         perror ("ERROR: ftruncate() failed");
//     }
//     shm = (char *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED,shm_fd,0);
//     *shm = '0';
//     if (shm == MAP_FAILED)
//     {
//         perror ("ERROR: mmap() failed");
//     }
//     return (shm);
// }
// void printValue(char* shm_addr){
    
//     printf ("data (@ %#x): '%s'\n", (unsigned int) shm_addr,shm_addr);
// }
// int main(){
//     pid_t   n1;      
//     pid_t   n2;      
    
//     printf("Main Program PID:%d\n",getpid());


//     int size = 4;

//     int rtn;
//     int count =1;
//     semP = sem_open(semPName, O_CREAT | O_EXCL, 0600, 1);
//     semGo = sem_open(semGoName, O_CREAT | O_EXCL, 0600, 0);

//     char*  shm_addr;

//     n1 = fork(); 
//     n2 = fork(); 
  
//     if (n1 > 0 && n2 > 0) { 
//         shm_addr = my_shm_create(shmName,size);
//         runParallel(shm_addr);
//         count +=1;
//     } 
//     else if (n1 == 0 && n2 > 0) 
//     { 
//       shm_addr =my_shm_open(shmName);
//       runParallel(shm_addr);
//       count +=1;
//     } 
//     else if (n1 > 0 && n2 == 0) 
//     {   
//       shm_addr =my_shm_open(shmName);
//       runParallel(shm_addr);
//       count +=1;
//     } 
//     else if(n1 == 0 && n2 == 0){   
//         shm_addr =my_shm_open(shmName);
//         runParallel(shm_addr);
//         count +=1;

//         sem_unlink(semPName);semGoName);

//         sem_destroy(semP);
//         sem_destroy(semGo);          
         
//     } 
//     return (0);
    
// }
