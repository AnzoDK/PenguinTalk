#pragma once
#include <vector>
#include <exception>
//Exceptions
class StoopidMapsBaseException : public std::exception
{
public:
    StoopidMapsBaseException(const char* msg) : std::exception()
    {
        unsigned int size = strlen(msg);
        m_errMsg = new char[size];
        memcpy(m_errMsg,msg,size);
    }
    ~StoopidMapsBaseException()
    {
        if(m_errMsg != 0x0)
        {
            delete[] m_errMsg;
        }
    }
    virtual const char* what() const noexcept
    {
        return m_errMsg;
    }
private:
    char* m_errMsg = 0x0;
};

class NoSuchKeyException : public StoopidMapsBaseException { NoSuchKeyException(const char* msg) : StoopidMapsBaseException(msg){} };
class KeyAlreadyPresentException : public StoopidMapsBaseException{ KeyAlreadyPresentException(const char* msg) : StoopidMapsBaseException(msg){} };


//Pairs
template<typename KeyType, typename ValueType>
class StoopidKeyPair
{
public:
    StoopidKeyPair();
    ~StoopidKeyPair();
    KeyType Key();
    ValueType Value();
};

//STUB
template<typename T>
class StoopidHashMap
{
    StoopidHashMap();
    ~StoopidHashMap();
};

//Maps
template<typename T>
class StoopidKeyMap
{
public:
    StoopidKeyMap();
    ~StoopidKeyMap();
    StoopidKeyPair<std::string, T>& operator[](const std::string& key) { return GetRef(key); }
    void Append(StoopidKeyPair<std::string, T> key);
    void Remove(std::string key);
    StoopidKeyPair<std::string, T> Get(const std::string& key);
    T GetValue(std::string key);
    StoopidKeyPair<std::string, T>& GetRef(const std::string& key);
protected:
    std::vector<StoopidKeyPair<std::string, T>>* m_keyMap = new std::vector<StoopidKeyPair<std::string, T>>();
private:
    
};

