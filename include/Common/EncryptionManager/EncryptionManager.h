#pragma once
#include <Common/EncryptionManager/RSAKey.h>
#include <Common/ManagedBuffer/ManagedBuffer.h>

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
