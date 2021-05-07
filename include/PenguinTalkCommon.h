#pragma once
#include <iostream>

// Inclutions for Linux libraries
#ifdef __linux__
#include <pthread.h>
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


// Adding the bzero and bcopy shortcuts from Linux into Windows
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)
#endif

#define DEFAULT_PORT 44344
#define DEFAULT_HOST "LocalHost"
/*ENUMS*/
enum InitStatus{CONN_SUCCESS=0, CONN_FAILED, PORT_IN_USE, BIND_FAILED, NO_HOST, CONN_ERROR};
enum ErrorState{NONE=0, SOCKET_READ_ERROR, SOCKET_WRITE_ERROR, ACCEPT_ERROR};
/*END*/

/*Global Functions*/
std::string g_GetInitError(int errCode)
{
    switch(errCode)
    {
        case CONN_SUCCESS:
            return "Connection Successful";
        case CONN_FAILED:
            return "Connection Failed";
        case PORT_IN_USE:
            return "Local port is already in use";
        case BIND_FAILED:
            return "Failed to bind to socket";
        case NO_HOST:
            return "Failed to resolve host";
        case CONN_ERROR:
            return "Failed to establish connection to host";
        default:
            return "Unknown Error";
    }
}

std::string g_GetSocketError(int errCode)
{
    switch(errCode)
    {
        case NONE:
            return "No Error";
        case SOCKET_READ_ERROR:
            return "Failed to read from socket";
        case SOCKET_WRITE_ERROR:
            return "Failed to write to socket";
        case ACCEPT_ERROR:
            return "Failed to accept connection";
        default:
            return "Unknown Error";
    }
}
/*Shifts buffer to the right ONLY if there are 0x0 bytes to overwrite*/
void g_ShiftBufferRight(char* buffer, int bufferSize, int shift)
{
    int activeIndex = -1;
    for(int i = 0; i < bufferSize; i++)
    {
        if (buffer[bufferSize-1-i] != 0x0)
        {
            activeIndex = bufferSize-i-1;
            break;
        }
    }
    if(activeIndex == -1)
    {
        activeIndex = 0;
    }
    if(activeIndex+shift >= bufferSize || activeIndex == 0)
    {
        //No space for shift
        std::cout << "No space for shift" << std::endl;
        return;
    }
    for(int i = 0; i < activeIndex; i++)
    {
        buffer[activeIndex+shift-i] = buffer[activeIndex-i];
    }
    for(int i = 0; i < shift; i++)
    {
        buffer[i] = 0x0;
    }
}
char* g_CopyBuffer(char* buffer, int start, int end)
{
    if(start > end)
    {
        //INVALID
        return nullptr;
    }
    int len = end-start;
    char* newBuff = new char[len];
    for(int i = 0; i < len; i++)
    {
        newBuff[i] = buffer[start+i];
    }
    return newBuff;
}
/*END*/
