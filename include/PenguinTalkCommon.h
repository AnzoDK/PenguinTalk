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
//#define _WINSOCKAPI_
#include <windows.h>
#include <winsock.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <AF_Irda.h>
//#include <in6addr.h>
//#include <mstcpip.h>
//#include <MSWSock.h>
//#include <mswsockdef.h>
//#include <nsemail.h>
//#include <NspAPI.h>
//#include <socketapi.h>
//#include <SpOrder.h>
//#include <transportsettingcommon.h>
//#include <WS2atm.h>
//#include <WS2spi.h>
//#include <WS2tcpip.h>
//#include <wsipv6ok.h>
//#include <WSNwLink.h>
//#include <wsrm.h>


#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)
#endif

#define DEFAULT_PORT 44344
#define DEFAULT_HOST "localhost"
/*ENUMS*/
enum InitStatus{CONN_SUCCESS=-1, CONN_FAILED, PORT_IN_USE, BIND_FAILED};
enum ErrorState{NONE=0, SOCKET_READ_ERROR, SOCKET_WRITE_ERROR, ACCEPT_ERROR, NO_HOST, CONN_ERROR};
/*END*/
