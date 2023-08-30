#pragma once
#include "_AccountSystem.h"
#include "../Common/EncryptionManager/RSAKey.h"
#include "../Common/StoopidMaps.h"
#include "./_DBManager.h"

class ServerAccountManager
{
public:
    ServerAccountManager(PenguinTalkDBManager& DBConn); //Just pass the
    ~ServerAccountManager();
    bool ChangeUsername(const std::string& keyThumbPrint, const std::string& newUsername);
    bool ChangeKey(const std::string& keyThumbPrint, RSAPublicKey* newKey);
    bool ChangeKey(RSAPublicKey* oldKey, RSAPublicKey* newKey);
    bool SetUserSettings(UserSettings settings);
    
protected:
    
private:
    bool m_SetUpDB();
    bool m_SyncToDB();
    bool m_LoadInitialStateFromDB();
    StoopidKeyMap<ServerUser>* m_users = new StoopidKeyMap<ServerUser>(); //This will act as a RAM cache
    PenguinTalkDBManager& m_DBConnector; //DO NOT DELTE - THIS OBJECT IS, AND SHOULD BE, MANAGED BY THE PENGUINTALK SERVER
};
