#pragma once
#include <iostream>
#include <exception>
#include <string.h>
#include <stdlib.h>
class NotImplementedException : public std::exception
{
public:
    NotImplementedException(const char* msg) : std::exception()
    {
        unsigned int size = strlen(msg);
        m_errMsg = new char[size];
        memcpy(m_errMsg,msg,size);
    }
    ~NotImplementedException()
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
