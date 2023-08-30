#pragma once
#include "../../StoopidDB/stoopidDB.h"
#include <future>
#include <iostream>

class PenguinTalkDBManager
{
public:
    PenguinTalkDBManager();
    static PenguinTalkDBManager* LoadOrCreateDB(const std::string& path);
    static PenguinTalkDBManager* LoadDB(const std::string& path);
    static bool CreateDB(const std::string& path);
    bool SwitchDB(const std::string& dbPath);
    std::string GetStoopidDBErrors(); //Call this if an error happens in StoopidDB to get an error log
    ~PenguinTalkDBManager();
    std::future<SQLResponse> QueueCommand(const std::string& sqlCommand);
    
protected:
    DBManager* m_DBManager = 0x0;
private:
    
};
