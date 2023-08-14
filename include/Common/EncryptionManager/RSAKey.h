#pragma once
#include <iostream>
#include "../PenguinTalkCommon.h"
#include "../ManagedBuffer/ManagedBuffer.h"

class RSAPublicKey
{
public:
    RSAPublicKey(byte* buffer, uint bufferSize);
    ~RSAPublicKey();
    byte* Encrypt(byte* buffer, uint bufferSize, uint& returnedBufferSize);
protected:
    ManagedBuffer m_buffer;
};

class RSAPrivateKey : public RSAPublicKey
{
public:
    RSAPrivateKey(byte* buffer, uint bufferSize);
    ~RSAPrivateKey();
    byte* Decrypt(byte* buffer, uint bufferSize, uint& returnedBufferSize);
    RSAPublicKey CreatePublicKey();
private:
    
};

struct RSAKey
{
    RSAPrivateKey privateKey;
    RSAPublicKey publicKey;
};

