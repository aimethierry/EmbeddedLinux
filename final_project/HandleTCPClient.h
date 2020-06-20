#ifndef _HANDLE_TCP_CLIENT_H_
#define _HANDLE_TCP_CLIENT_H_
#include <semaphore.h>

extern void HandleTCPClient (int clntSocket, sem_t* semController);   /* TCP client handling function */

#endif
