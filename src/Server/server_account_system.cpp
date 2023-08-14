#include "../../include/Server/_AccountSystem.h"

//AutoSortArray

template<typename T, typename U, typename Z>
AutoSortArray<T,U,Z>::AutoSortArray(T size)
{
    m_size = size;
    m_freeSpace = size;
    
    m_buffer = new U[m_size];
}

template<typename T, typename U, typename Z>
AutoSortArray<T,U,Z>::~AutoSortArray()
{
    delete[] m_buffer;
}



//UserGroup

// bool UserGroup::IsLargerThan(AutoSortableBase& other)
// {
//     UserGroup g = dynamic_cast<UserGroup&>(other);
//     return m_id > g.GetID();
// }
// 
// bool UserGroup::IsSmallerThan(AutoSortableBase& other)
// {
//     UserGroup g = dynamic_cast<UserGroup&>(other);
//     return m_id < g.GetID();
// }



UserGroup* ServerGroups::ContainsGroupOrNull(std::string groupName)
{
    //Slow AF search algo... //TODO Please optimize!!
    uint64_t id = 0;
    while(id < 1)
    {
        
    }
    return nullptr; //NOT DONE
}

UserGroup* ServerGroups::ContainsGroupOrNull(uint64_t id)
{
    UserGroup* g = nullptr;
    try{
        g = &ServerGroups[id]; //Direct access to object
    }
    catch(std::exception e)
    { /* Ignore */ }
    return g;
}

//UserBase + ServerUser
UserBase::UserBase(RSAPublicKey* userKey)
{
    //Clone key
    
}

ServerUser::ServerUser(RSAPublicKey* userKey) : UserBase(userKey)
{
    
}


