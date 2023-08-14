#pragma once
#include "../PenguinTalkCommon.h"
//#include "../EncryptionManager/EncryptionManager.h"

class Encryptor;

class ManagedBuffer
{
public:
    ManagedBuffer();
    ManagedBuffer(size_t size);
    ManagedBuffer(const ManagedBuffer& buff);
    ManagedBuffer(byte* buffer, size_t bufferSize);
    ~ManagedBuffer();
    size_t GetSize();
    void New(size_t size);
    void Clear();
    byte CopyRead(size_t index);
    byte& operator[](size_t index);
    void Destory();
    //bool Encrypt(Encryptor& encryptor);
    //bool Decrypt(Encryptor& encryptor);
private:
    void m_CloneBuffer(byte* buff, size_t size);
    void m_DeleteInternalBuffer();
    void m_CreateEmptyBuffer(size_t size);
    void m_ResetBuffer();
protected:
    size_t m_bufferSize = 0;
    byte* m_buffer = 0x0; 
};
