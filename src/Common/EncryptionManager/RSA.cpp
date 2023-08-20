#include "../../../include/Common/EncryptionManager/RSAKey.h"
#include "../../../include/Common/Exceptions/PenguinTalkExceptions.h"
//Public Key

RSAPublicKey::RSAPublicKey(byte* buffer, uint bufferSize)
{
    //Clone Buffer
    m_buffer = new ManagedBuffer(buffer, bufferSize);
}


RSAPublicKey::~RSAPublicKey()
{
     if(m_buffer != 0x0)
    {
        m_buffer->Destory();
        delete m_buffer;
        m_buffer = 0x0; //I love adding these to make memory control better for me, even if it does slow things down, Especially here where the object is being destroyed - But it wouldn't be the first time I made a horrible program trying to delete the same object twice...
    }
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
    if(m_buffer != 0x0)
    {
        m_buffer->Destory();
        delete m_buffer;
        m_buffer = 0x0; //I love adding these to make memory control better for me, even if it does slow things down, Especially here where the object is being destroyed - But it wouldn't be the first time I made a horrible program trying to delete the same object twice...
    }
}

byte * RSAPrivateKey::Decrypt(byte* buffer, uint bufferSize, uint& returnedBufferSize)
{
    throw NotImplementedException("Decryption is not yet implemented");
}

RSAPublicKey RSAPrivateKey::CreatePublicKey()
{
    throw NotImplementedException("PublicKey from PrivateKey creation is not yet implemented");
}

//RSAKey

RSAKey::~RSAKey()
{
    if(publicKey != 0x0)
    {
        delete publicKey;
    }
    
    if(privateKey != 0x0)
    {
        delete privateKey;
    }
}

void RSAKey::GenerateKey()
{
    RSA_generate_key();
}






