#ifndef SHMWRITE_H
#define SHMWRITE_H
#define success 0
#define fail -1

int createMemory(char * shm_name, int size);
int  writeIntoMemory(char * shm_name,  char * message);

#endif