#include "../../include/Server/_AccountManagement.h"

ServerAccountManager::ServerAccountManager(PenguinTalkDBManager& dbMan) : m_DBConnector(dbMan)
{
    m_SetUpDB();
}

ServerAccountManager::~ServerAccountManager()
{
    if(m_users != 0x0)
    {
        delete m_users;
        m_users = 0x0;
    }
}

bool ServerAccountManager::m_SyncToDB()
{
    
}

bool ServerAccountManager::m_SetUpDB()
{
    std::string sqlCmd = "CREATE TABLE IF NOT EXISTS users (pubkey nvarchar(4096), username nvarchar(255), _ID int(8));";
    std::future<SQLResponse> sqlRes = m_DBConnector.QueueCommand(sqlCmd);
    sqlRes.wait(); //Wait for DB to create the table
    SQLResponse response = sqlRes.get();
    if(response.code != SQLResponseCode::SQL_OK)
    {
        std::cout << "Server failed to setup DataBase... Error: \"Code: '" << response.code << "' Msg: '" << m_DBConnector.GetStoopidDBErrors() << "'\"";
        return 0;
    }
    return 1;
}
