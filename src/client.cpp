#include "../include/PenguinTalkClient.h"
#include <iostream>



Client::Client()
{
    m_host = DEFAULT_HOST;
    m_port = DEFAULT_PORT;
}

int Client::Init()
{
#ifdef _WIN32
    WORD wV = MAKEWORD(2, 2);
    WSADATA wsaData;
    WSAStartup(wV, &wsaData);
#endif
    m_fd = socket(AF_INET,SOCK_STREAM,0);
    if(m_fd < 0)
    {
        return CONN_FAILED;
    }
    m_server = (hostent*)gethostbyname(m_host.c_str());
    if(m_server == NULL)
    {
       return NO_HOST;
    }
    sockaddr_in serv_addr = sockaddr_in();
    serv_addr.sin_family = AF_INET;
    bcopy((char *)m_server->h_addr, (char *)&serv_addr.sin_addr.s_addr,m_server->h_length);
    serv_addr.sin_port = htons(m_port);
    if(connect(m_fd,(sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
    {
        return CONN_ERROR;
    }
    return NONE;
}

#ifdef __linux__
int Client::GetInput()
{
    printf("Please enter the message: ");
    bzero(m_msgBuffer,256);
    fgets(m_msgBuffer,255,stdin);
    int n = write(m_fd,m_msgBuffer,strlen(m_msgBuffer));
    if(n < 0)
    {
        return SOCKET_WRITE_ERROR;
    }
    bzero(m_msgBuffer,256);
    n = read(m_fd,m_msgBuffer,255);
    if(n < 0)
    {
        return SOCKET_READ_ERROR;
    }
    printf("%s\n",m_msgBuffer);
    close(m_fd);
    return 0;
}
#endif

#ifdef _WIN32
int Client::GetInput()
{
    printf("Please enter the message: ");
    bzero(m_msgBuffer, 256);
    fgets(m_msgBuffer, 255, stdin);
    int n = send(m_fd, m_msgBuffer, strlen(m_msgBuffer), 0);
    if (n < 0)
    {
        return SOCKET_WRITE_ERROR;
    }
    bzero(m_msgBuffer, 256);
    n = recv(m_fd, m_msgBuffer, 255, 0);
    if (n < 0)
    {
        return SOCKET_READ_ERROR;
    }
    printf("%s\n", m_msgBuffer);
    closesocket(m_fd);
    return 0;
}
#endif

int main()
{
    Client c = Client();
    int err = c.Init();
    if (err != 0)
    {
        std::cout << g_GetInitError(err) << std::endl;
        exit(1);
    }
    err = c.GetInput();
    if (err != 0)
    {
        std::cout << g_GetSocketError(err) << std::endl;
        exit(1);
    }
    return 0;
}
