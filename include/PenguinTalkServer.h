#pragma once
#include <iostream>
#include <algorithm>
#include "stoopidDB.h"
#include "PenguinTalkCommon.h"



struct Connection
{
public:
    Connection(){}
    Connection(bool _state, int _fd){state = _state; id=_fd;}
    int id = -1;
    bool state = false;
};

class Server
{
public:
    Server();
    Server(int port, std::string host);
    int Init(int maxThreads=5);
    int Start();
    ~Server(){}

private:
    int m_PrepareDB();
    void m_SetSocketTimeout(int fd, int seconds);
    std::string m_GenerateToken(std::string userName);
    void m_CheckCertificate();
    int m_msgSize = 2048;
    char* m_msgBuffer;
    DBManager m_DBMan;
    int m_port = 0;
    std::string m_host = "";
    int m_maxThreads = 0;
    int* m_threadIDs = nullptr;
#ifdef __linux__
    int m_fd = -1;
#elif _WIN32
    SOCKET m_fd = 0;
#endif
};
