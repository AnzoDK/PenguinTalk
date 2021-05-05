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
int m_fd = -1;
char m_msgBuffer[256];
hostent* m_server;
};
