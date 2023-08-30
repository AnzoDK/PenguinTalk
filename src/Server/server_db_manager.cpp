#include "../../include/Server/_DBManager.h"
#include <filesystem>

PenguinTalkDBManager::PenguinTalkDBManager()
{
    
}

PenguinTalkDBManager::~PenguinTalkDBManager()
{
    if(m_DBManager != 0x0)
    {
        delete m_DBManager;
    }
}


bool PenguinTalkDBManager::CreateDB(const std::string& path)
{
    DBManager tmpDBMan = DBManager();
    return tmpDBMan.CreateDB(path);
}

std::future<DBRow> PenguinTalkDBManager::QueueCommand(const std::string& sqlCommand)
{
    return std::future<DBRow>();
}

PenguinTalkDBManager* PenguinTalkDBManager::LoadDB(const std::string& path)
{
    PenguinTalkDBManager* dbMan = new PenguinTalkDBManager();
    dbMan->m_DBManager = new DBManager(path);
    return dbMan;
}

PenguinTalkDBManager * PenguinTalkDBManager::LoadOrCreateDB(const std::string& path)
{
    if(std::filesystem::exists(path))
    {
        return LoadDB(path);
    }
    CreateDB(path);
    return LoadDB(path);
}
bool PenguinTalkDBManager::SwitchDB(const std::string& dbPath)
{
    return m_DBManager->LoadDB(dbPath);
}

std::string PenguinTalkDBManager::GetStoopidDBErrors()
{
    return m_DBManager->Error();
}


