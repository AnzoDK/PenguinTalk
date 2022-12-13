#include <Server/PenguinTalkServer.h>
#include <Common/ManagedBuffer/ManagedBuffer.h>
#include <Common/EncryptionManager/EncryptionManager.h>
#include <iostream>

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char** argv)
{
    int port = DEFAULT_PORT;
    std::string host = DEFAULT_HOST;
    if(cmdOptionExists(argv,argv+argc,"--port"))
    {
        port = std::stoi(getCmdOption(argv,argv+argc,"--port"));
    }
    if(cmdOptionExists(argv,argv+argc,"--host"))
    {
        host = getCmdOption(argv,argv+argc,"--host");
    }
    /*Server s = Server(port,host);
    int err = s.Init();
    if(err != 0)
    {
        std::cout << g_GetInitError(err) << std::endl;
        exit(1);
    }
    err = s.Start();
    if(err != 0)
    {
        std::cout << g_GetSocketError(err) << std::endl;
        exit(1);
    }*/
    ManagedBuffer buff = ManagedBuffer();
    Encryptor ec = Encryptor();
}
