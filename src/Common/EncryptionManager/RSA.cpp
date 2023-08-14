#include "../../../include/Common/EncryptionManager/RSAKey.h"
#include "../../../include/Common/Exceptions/PenguinTalkExceptions.h"

//Public Key

RSAPublicKey::RSAPublicKey(byte* buffer, uint bufferSize)
{
    //Clone Buffer
    m_buffer = ManagedBuffer(buffer, bufferSize);
}


RSAPublicKey::~RSAPublicKey()
{
    m_buffer.Destory();
}

byte* RSAPublicKey::Encrypt(byte* buffer, uint bufferSize, uint& returnedBufferSize)
{
    throw NotImplementedException("Encryption is not yet implemented");
}


//PrivateKey

RSAPrivateKey::RSAPrivateKey(byte* buffer, uint bufferSize) : RSAPublicKey(buffer, bufferSize)
{
    
}

RSAPrivateKey::~RSAPrivateKey()
{
    m_buffer.Destory();
}

byte * RSAPrivateKey::Decrypt(byte* buffer, uint bufferSize, uint& returnedBufferSize)
{
    throw NotImplementedException("Decryption is not yet implemented");
}

RSAPublicKey RSAPrivateKey::CreatePublicKey()
{
    throw NotImplementedException("PublicKey from PrivateKey creation is not yet implemented");
}




