#pragma once
#include <iostream>
#include <algorithm>
#include <Common/PenguinTalkCommon.h>
#include "_DBManager.h"


class Server
{
public:
    Server(const std::string& DBpath);
    ~Server();
    void Init();
    void Stop();
    void Loop();
protected:
    void m_CreateOrConnectToDB(const std::string& DBpath);
    bool m_shouldStop = false;
    PenguinTalkDBManager* m_DBMan = 0x0;
private:
    
};
