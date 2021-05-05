#pragma once
#include <iostream>
#include "PenguinTalkCommon.h"


class Server
{
public:
    Server();
    Server(int port, std::string host);
    int Init();
    int Start();

private:
    char m_msgBuffer[256];
    int m_port = 0;
    std::string m_host = "";
#ifdef __linux__
    int m_fd = -1;
#elif _WIN32
    SOCKET m_fd = 0;
#endif
};