#pragma once
#include <iostream>
#include <Common/PenguinTalkCommon.h>

class RSAPublicKey
{
public:
    RSAPublicKey(byte* buffer, uint bufferSize);
    ~RSAPublicKey();
private:
};

class RSAPrivateKey
{
public:
    RSAPrivateKey();
    ~RSAPrivateKey();
private:

};

struct RSAKey
{
    RSAPrivateKey privateKey;
    RSAPublicKey publicKey;
};

