#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define DEFAULT_PORT 44344
#define DEFAULT_HOST "localhost"
/*ENUMS*/
enum InitStatus{CONN_SUCCESS=-1, CONN_FAILED, PORT_IN_USE, BIND_FAILED};
enum ErrorState{NONE=0, SOCKET_READ_ERROR, SOCKET_WRITE_ERROR, ACCEPT_ERROR, NO_HOST, CONN_ERROR};
/*END*/
