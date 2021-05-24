#pragma once
#include <iostream>
#include "PenguinTalkCommon.h"

class Client
{
public:
    Client();
    ~Client()
    {
        delete[] m_msgBuffer; 
        #ifdef __linux__ 
        EVP_PKEY_free(m_secKey);
        #endif
        
    }
    int Init();
    int GetInput();
    int Aurthorize();
    Client(uint16_t port, std::string host);
private:
    void m_GenerateKey();
    void m_InitEncrypt();
    uint16_t m_port = 0;
    std::string m_host = "";
    int m_msgSize = 2048;
    char* m_msgBuffer;
#ifdef __linux__
    int m_fd = -1;
    EVP_PKEY* m_secKey;
#elif _WIN32
    SOCKET m_fd = 0;
#endif
    hostent* m_server;
};
