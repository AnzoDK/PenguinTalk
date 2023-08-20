#pragma once
#include "_AccountSystem.h"
#include "../Common/EncryptionManager/RSAKey.h"
#include "../Common/StoopidMaps.h"

class ServerAccountManager
{
public:
    ServerAccountManager();
    ~ServerAccountManager();
    bool ChangeUsername(const std::string& keyThumbPrint, const std::string& newUsername);
    bool ChangeKey(const std::string& keyThumbPrint, RSAPublicKey* newKey);
    bool ChangeKey(RSAPublicKey* oldKey, RSAPublicKey* newKey);
    bool SetUserSettings(UserSettings settings);
    
protected:
    
private:
    StoopidKeyMap<ServerUser>* m_users = new StoopidKeyMap<ServerUser>();
};
