#pragma once
#include "RSAKey.h"
#include "../ManagedBuffer/ManagedBuffer.h"

class ManagedBuffer;

class Encryptor
{
public:
    Encryptor(){};
    void LoadPubKey(RSAPublicKey key);
    void LoadPrivateKey(RSAPrivateKey key);
    bool EncryptBuffer(ManagedBuffer& plainTextManagedBuffer){return false;};
    bool DecryptBuffer(ManagedBuffer& encryptedManagedBuffer){return false;};
    ~Encryptor(){};
private:
};
