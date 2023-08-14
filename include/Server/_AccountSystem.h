#pragma once
#include "../Common/PenguinTalkCommon.h"
#include <vector>
#include "../Common/EncryptionManager/RSAKey.h"
#include "../Common/AccountRoles/AccountRoles.h"

class AutoSortableBase
{
public:
    AutoSortableBase(){};
    ~AutoSortableBase(){};
    virtual bool IsSmallerThan(AutoSortableBase& other){return true;};
    virtual bool IsLargerThan(AutoSortableBase& other){return true;};
    
};

//Enable only if type is uint32_t or uint64_t
template <typename T, typename U, typename = typename std::enable_if<std::is_same<T,uint32_t>::value || std::is_same<T,uint64_t>::value>::type>
class AutoSortArray
{
public:
    AutoSortArray(T size);
    ~AutoSortArray();
    
private:
    
    U* m_buffer;
    T m_size;
    T m_freeSpace;
};

class UserGroup
{
public:
    UserGroup(){};
    ~UserGroup(){};
    uint64_t GetID(){return m_id;};
    
private:
    uint64_t m_id = 0;
    std::string m_name;
protected:
    
};

class UserBase
{
public:
    UserBase(RSAPublicKey* userKey);
    ~UserBase()
    {
        if(m_userKey != 0x0)
        {
            delete m_userKey;
        }
    };
    uint64_t GetID(){return m_id;};
protected:
    uint64_t m_id = 0x0;
    RSAPublicKey* m_userKey = 0x0;
};

class ServerUser : public UserBase
{
public:
    ServerUser(RSAPublicKey* userKey);
    ~ServerUser(){m_userGroups.clear();};
private:
    
protected:
    std::vector<uint64_t> m_userGroups = std::vector<uint64_t>();
    AccountRole m_serverRole = USER; //Default to user, as owners are only set once, when the server is created or when the server owner wilfully changes the ownerkey
    
};


class ServerGroups
{
public:
    UserGroup* ServerGroups = nullptr;
    UserGroup* ContainsGroupOrNull(std::string groupName);
    UserGroup* ContainsGroupOrNull(uint64_t id);
};
