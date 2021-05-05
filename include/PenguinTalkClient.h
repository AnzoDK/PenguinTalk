#pragma once
#include <iostream>
#include "PenguinTalkCommon.h"

class Client
{
public:
    Client();
    int Init();
    int GetInput();
    Client(uint16_t port, std::string host);
private:
uint16_t m_port = 0;
std::string m_host = "";
#ifdef __linux__
int m_fd = -1;
#elif _WIN32
SOCKET m_fd = 0;
#endif
char m_msgBuffer[256];
hostent* m_server;
};
