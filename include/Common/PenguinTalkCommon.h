#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <filesystem>
// Inclusions for Linux libraries
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
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <time.h>
#endif

// Inclustions for Windows libraries
#ifdef _WIN32
#include <windows.h>
#include <winsock.h>


// Adding the bzero and bcopy shortcuts from Linux into Windows
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)

// Define types
typedef unsigned int uint;
#endif

#define FPS(start) (CLOCKS_PER_SEC / (clock()-start))
#define DEFAULT_PORT 44344
#define DEFAULT_HOST "localhost"
#ifndef __byte
typedef unsigned char __byte;
#ifndef byte
typedef __byte byte;
#endif
#endif

namespace fs = std::filesystem;

/*ENUMS*/
enum InitStatus{CONN_SUCCESS=0, CONN_FAILED, PORT_IN_USE, BIND_FAILED, NO_HOST, CONN_ERROR};
enum ErrorState{ERROR_NONE=0, SOCKET_READ_ERROR, SOCKET_WRITE_ERROR, ACCEPT_ERROR};
/*END*/

/*Global Functions*/
static std::string g_GetInitError(int errCode)
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

//Returns array of same size as the input array
static unsigned char* g_ToUnsignedBuffer(char* in, int inSize)
{
   unsigned char* ret = new unsigned char[inSize];
   for(int i = 0; i < inSize; i++)
   {
       ret[i] = static_cast<unsigned char>(in[i]);
   }
   return ret;
}

//Returns array of same size as the input array
static char* g_ToSignedBuffer(unsigned char* in, int inSize)
{
   char* ret = new char[inSize];
   for(int i = 0; i < inSize; i++)
   {
       ret[i] = static_cast<char>(in[i]);
   }
   return ret;
}

static std::string g_GetSocketError(int errCode)
{
    switch(errCode)
    {
        case ERROR_NONE:
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
static void g_ShiftBufferRight(char* buffer, int bufferSize, int shift)
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
static char* g_CopyBuffer(char* buffer, int start, int end)
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

/*Extra Classes and code*/
struct JsonKey
{
    JsonKey(std::string _name, std::string _value){name = _name, value = _value;};
    std::string name;
    std::string value;
};


class JsonHandler
{
public:
    JsonHandler(std::string jsonString){m_workString = jsonString;keys = std::vector<JsonKey>();};
    std::string GetVariable(std::string q)
    {
        size_t index = -1;
        for(size_t i = 0; i < keys.size();i++)
        {
            if(keys.at(i).name == q)
            {
                index = i;
                break;
            }
        }
        if(index == -1)
        {
            return "";
        }
        return keys.at(index).value;
    }
    std::string* GetArray(std::string q, size_t &arrLen)
    {
        std::string* arr;
        size_t index = -1;
        for(size_t i = 0; i < keys.size();i++)
        {
            if(keys.at(i).name == q)
            {
                index = i;
                break;
            }
        }
        if(index == -1)
        {
            return nullptr;
        }
        size_t oldIndex = keys.at(index).value.find_first_of('"',0);
        size_t discoverOldIndex = keys.at(index).value.find_first_of('"',0);
        size_t tmpSize = 0;
        while(true)
        {
            if(discoverOldIndex != std::string::npos)
            {
                tmpSize++;
                discoverOldIndex = keys.at(index).value.find_first_of('"',discoverOldIndex+1);
            }
            else
            {
                break;
            }
        }
        if(tmpSize%2 != 0)
        {
            //Json Syntax Error
            return nullptr;
        }
        arrLen = tmpSize/2;
        arr = new std::string[arrLen];
        size_t count = 0;
        while(true)
        {
            size_t newIndex = keys.at(index).value.find_first_of('"',oldIndex+1);
            if(newIndex != std::string::npos)
            {
                arr[count] = keys.at(index).value.substr(oldIndex+1,newIndex-oldIndex);
                count++;
            }
            else
            {
                break;
            }
            oldIndex = newIndex;
        }
        return arr;
    }
    bool Process()
    {
        if(m_workString.at(0) != '{' || m_workString.at(m_workString.length()-1) != '}')
        {
            return false;  
        }
        //m_workString.erase(std::remove_if(m_workString.begin(), m_workString.end(), ::isspace), m_workString.end());
        bool spaceAllowed = false;
        for(size_t i = 0; i < m_workString.length();i++)
        {
            if(m_workString.at(i) == '"')
            {
                spaceAllowed = !spaceAllowed;
            }
            if(m_workString.at(i) == ' ')
            {
                if(!spaceAllowed)
                {
                    m_workString.erase(i,1);
                    i--;
                }
            }
        }
        size_t oldIndex = m_workString.find_first_of('"',0);
        while(true)
        {
            size_t tmpIndex = m_workString.find_first_of('"',oldIndex+1);
            if(tmpIndex == std::string::npos)
            {
                break;
            }
            if(m_workString.at(tmpIndex+1) != ':')
            {
                //Invalid Syntax
                return false;
            }
            size_t comma = m_workString.find_first_of(',',tmpIndex);
            size_t square = m_workString.find_first_of('[',tmpIndex);
            if(square != std::string::npos)
            {
                size_t squareEnd = m_workString.find_first_of(']',tmpIndex);
                if(squareEnd == std::string::npos)
                {
                    //Invalid Syntax
                    return false;
                }
                else
                {
                    comma = squareEnd+1;
                }
            }
            if(m_workString.at(comma) != ',')
            {
                //Invalid Syntax
                return false;
            }
            if(m_workString.at(comma-1) != '"' && m_workString.at(comma-1) != ']')
            {
                //Invalid Syntax
                return false;
            }
            
            JsonKey tmpKey = JsonKey(m_workString.substr(oldIndex+1,tmpIndex),m_workString.substr(tmpIndex+2,comma-1-tmpIndex));
            keys.push_back(tmpKey);
            oldIndex = comma;
            
        }
        return true;
    }
private:
    std::string m_workString;
    std::vector<JsonKey> keys;
};
/*END*/
