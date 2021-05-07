#include "../include/PenguinTalkServer.h"
#include <iostream>



Server::Server()
{
    m_host = DEFAULT_HOST;
    m_port = DEFAULT_PORT;
}
int Server::Init(int maxThreads)
{
#ifdef _WIN32
    WORD wV = MAKEWORD(2, 2);
    WSADATA wsaData;
    WSAStartup(wV, &wsaData);
#endif
    m_maxThreads = maxThreads;
    m_threadIDs = new int[m_maxThreads];
    m_fd = socket(AF_INET,SOCK_STREAM,0);
    if(m_fd < 0)
    {
        return CONN_FAILED;
    }
    sockaddr_in server_addr = sockaddr_in();
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(static_cast<uint16_t>(m_port));
    if(bind(m_fd,(sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
        return BIND_FAILED;
    }
    return CONN_SUCCESS;
}


#ifdef __linux__
int Server::Start()
{
    listen(m_fd,m_maxThreads);
    while(1)
    {
    sockaddr_in client_addr = sockaddr_in();
    socklen_t client_addr_len = sizeof(client_addr);
    int acc_socket = accept(m_fd,(sockaddr*)&client_addr,&client_addr_len);
    if(acc_socket < 0)
    {
        return ACCEPT_ERROR;
    }
    bzero(m_msgBuffer,256);
    int n = read(acc_socket,m_msgBuffer,255);
    if(n < 0)
    {
        return SOCKET_READ_ERROR;
    }
    n = write(acc_socket,"Data Recieved",13);
    close(acc_socket);
    //close(m_fd);
    std::cout << std::string(m_msgBuffer) << std::endl;
    if(std::string(g_CopyBuffer(m_msgBuffer,0,5)) == "cred=")
    {
        //TODO
        //Assign name to client here
    }
    }
    return NONE;
}
#endif

#ifdef _WIN32
int Server::Start()
{
    listen(m_fd, 5);
    sockaddr_in client_addr = sockaddr_in();
    int client_addr_len = sizeof(client_addr);
    int acc_socket = accept(m_fd, (sockaddr*)&client_addr, &client_addr_len);
    if (acc_socket < 0)
    {
        return ACCEPT_ERROR;
    }
    bzero(m_msgBuffer, 256);
    int n = recv(acc_socket, m_msgBuffer, 255, 0);
    if (n < 0)
    {
        return SOCKET_READ_ERROR;
    }
    n = send(acc_socket, "Data Recieved", 13, 0);
    closesocket(acc_socket);
    closesocket(m_fd);
    std::cout << std::string(m_msgBuffer) << std::endl;
    return NONE;
}
#endif

int main()
{
    Server s = Server();
    s.Init();
    s.Start();
}
