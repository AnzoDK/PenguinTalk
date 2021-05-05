#pragma once
#include <iostream>

// Inclutions for Linux libraries
#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

// Inclustions for Windows libraries
#ifdef _WIN32
#include <windows.h>
#include <winsock.h>



#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)
#endif

#define DEFAULT_PORT 44344
#define DEFAULT_HOST "localhost"
/*ENUMS*/
enum InitStatus{CONN_SUCCESS=-1, CONN_FAILED, PORT_IN_USE, BIND_FAILED};
enum ErrorState{NONE=0, SOCKET_READ_ERROR, SOCKET_WRITE_ERROR, ACCEPT_ERROR, NO_HOST, CONN_ERROR};
/*END*/
