#include "../../include/Server/PenguinTalkServer.h"


Server::Server(const std::string& DBPath)
{
    m_shouldStop = true;
    m_CreateOrConnectToDB(DBPath);
}

Server::~Server()
{
    
}

void Server::Init()
{
    
}

void Server::Stop()
{
    
}

void Server::Loop()
{
    while(!m_shouldStop)
    {
        
    }
    return;
}

void Server::m_CreateOrConnectToDB(const std::string& DBPath)
{
    m_DBMan = PenguinTalkDBManager::LoadOrCreateDB(DBPath);
}

