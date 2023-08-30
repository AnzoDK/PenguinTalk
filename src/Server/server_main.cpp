#include <Server/PenguinTalkServer.h>
#include "../../include/Common/ManagedBuffer/ManagedBuffer.h"
#include "../../include/Common/EncryptionManager/EncryptionManager.h"
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
    std::string dbPath = "./ptserver.sdb";
    if(cmdOptionExists(argv,argv+argc,"--port"))
    {
        port = std::stoi(getCmdOption(argv,argv+argc,"--port"));
    }
    if(cmdOptionExists(argv,argv+argc,"--host"))
    {
        host = getCmdOption(argv,argv+argc,"--host");
    }
    if(cmdOptionExists(argv,argv+argc,"--dbpath"))
    {
        dbPath = getCmdOption(argv,argv+argc,"--dbpath");
    }
    Server s = Server(dbPath);
    s.Init();
    auto serverLoop = std::async(std::launch::async, &Server::Loop, s); //Run loop on another thread
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
    //ManagedBuffer buff = ManagedBuffer();
    //Encryptor ec = Encryptor();
}
