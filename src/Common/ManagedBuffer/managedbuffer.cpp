#include <Common/ManagedBuffer/ManagedBuffer.h>
#include <cstring>

ManagedBuffer::ManagedBuffer(){}

ManagedBuffer::~ManagedBuffer()
{
    m_DeleteInternalBuffer();
}
ManagedBuffer::ManagedBuffer(size_t size)
{
    m_CreateEmptyBuffer(size);
}
size_t ManagedBuffer::GetSize()
{
    return m_bufferSize;
}
ManagedBuffer::ManagedBuffer(byte* buffer, size_t bufferSize)
{
    m_CloneBuffer(buffer,bufferSize);
}
ManagedBuffer::ManagedBuffer(const ManagedBuffer& buff)
{
    m_CloneBuffer(buff.m_buffer, buff.m_bufferSize);
}


void ManagedBuffer::New(size_t size)
{
    m_CreateEmptyBuffer(size);
}

void ManagedBuffer::Clear()
{
    m_ResetBuffer();
}

byte ManagedBuffer::CopyRead(size_t index)
{
    return m_buffer[index];
}

bool ManagedBuffer::Decrypt(Encryptor& encryptor)
{
    if(m_buffer == 0x0)
    {
        return false;
    }
    return encryptor.DecryptBuffer(*this);
}

bool ManagedBuffer::Encrypt(Encryptor& encryptor)
{
    if(m_buffer == 0x0)
    {
        return false;
    }
    return encryptor.EncryptBuffer(*this);
}




byte& ManagedBuffer::operator[](size_t index)
{
    return m_buffer[index];
}



void ManagedBuffer::m_ResetBuffer()
{
    memset(m_buffer,0x0,m_bufferSize);
}

void ManagedBuffer::m_CreateEmptyBuffer(size_t size)
{
    m_DeleteInternalBuffer();
    m_buffer = new byte[size];
    m_bufferSize = size;
    memset(m_buffer,0x0,size); //reset buffer;
}

void ManagedBuffer::m_DeleteInternalBuffer()
{
    if(m_buffer == 0x0)
    {
        delete[] m_buffer;
        m_buffer = 0x0;
    }
    m_bufferSize = 0;
}

void ManagedBuffer::m_CloneBuffer(byte* buff, size_t size)
{
    m_DeleteInternalBuffer();
    m_buffer = new byte[size];
    for(size_t i = 0; i < size; i++)
    {
        m_buffer[i] = buff[i];
    }
    m_bufferSize = size;
}





