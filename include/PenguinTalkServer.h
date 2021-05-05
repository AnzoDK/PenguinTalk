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
    int m_fd = -1;
};