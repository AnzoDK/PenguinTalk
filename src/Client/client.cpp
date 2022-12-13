#include "<Client/PenguinTalkClient.h>"
#include <iostream>

/*
 DISCLAIMER:
 THIS CLIENT IS NOT MEANT TO BE THE FINAL CLIENT AND SHOULD ONLY BE USED TO TEST THE CONNECTION BETWEEN THE SERVER AND A POTENTIAL CLIENT
 */

Client::Client()
{
    m_host = DEFAULT_HOST;
    m_port = DEFAULT_PORT;
    m_msgBuffer = new char[m_msgSize];
#ifdef __linux__
    m_secKey = EVP_PKEY_new();
#endif
}

int Client::Init()
{
#ifdef _WIN32
    WORD wV = MAKEWORD(2, 2);
    WSADATA wsaData;
    WSAStartup(wV, &wsaData);
#endif
    m_GenerateKey();
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
    m_InitEncrypt();
    return CONN_SUCCESS;
}

#ifdef __linux__
void Client::m_GenerateKey()
{
    std::cout <<"Generating Key" << std::endl;
    //Generate
    BIGNUM* bn = BN_new();
    BN_set_word(bn,RSA_F4);
        
    RSA* rsa = RSA_new();
    RSA_generate_key_ex(
        rsa, //RSA structure
        2048, //Bitlengh
        bn, //bn structure
        NULL
    );
    BN_free(bn);
    EVP_PKEY_assign_RSA(m_secKey,rsa);
    
}
void Client::m_InitEncrypt()
{
    //Start transaction
    int n = write(m_fd,"AUTH_START",10);
    
    //Read AUTH_START response and print it
    n = read(m_fd,m_msgBuffer,m_msgSize);
    std::cout << std::string(m_msgBuffer) << std::endl;
    
    //Reset msg buffer
    bzero(m_msgBuffer,m_msgSize);
    
    //Read the certifcate
    n = read(m_fd,m_msgBuffer,m_msgSize);
    
    if(n <= 0)
    {
        std::cout << "Failed to recieve message" << std::endl;
        close(m_fd);
        exit(1);
    }
    else
    {
        std::cout << "Recieved " << n << " Bytes" << std::endl;
    }
    
    //Copy the certifcate bytes from the msg buffer to its own buffer
    
    /*unsigned char* tmpBuff = new unsigned char[n];
    for(int i = 0; i < n; i++)
    {
        tmpBuff[i] = static_cast<unsigned char>(m_msgBuffer[i]);
    }*/
    
    char* tmpBuff = new char[n];
    for(int i = 0; i < n; i++)
    {
        tmpBuff[i] = m_msgBuffer[i];
    }
    bzero(m_msgBuffer,m_msgSize);
    
    //Reconstruct the certifcate from bytes
    X509* x509 = X509_new();
    BIO* x509_bio = BIO_new(BIO_s_mem());
    BIO_puts(x509_bio, tmpBuff);
    
    x509 = PEM_read_bio_X509(x509_bio,NULL,0,NULL);
    
    //Create the RSA handler for the encryption
    RSA* rsa = RSA_new();
    
    EVP_PKEY* serverPubKey = X509_get_pubkey(x509);
    
    rsa = EVP_PKEY_get1_RSA(serverPubKey);
    
    //Create the Hello Word data
    
    //NOTE: Inputs into RSA_private_decrypt should always be RSA_size(rsa)-42 ling. Where 42 is a constant for the RSA_PKCS1_OAEP_PADDING mode.
    
    
    std::string helloWorld = "Hello World!";
    unsigned char* buff = new unsigned char[RSA_size(rsa)-42];
    bzero(buff,RSA_size(rsa)-42);
    for(int i = 0; i < helloWorld.length();i++)
    {
        buff[i] = static_cast<unsigned char>(helloWorld.at(i));
    }
    unsigned char* encBuff = new unsigned char[RSA_size(rsa)];
    
    //Encrypt Data
    RSA_public_encrypt(RSA_size(rsa)-42,buff,encBuff,rsa,RSA_PKCS1_OAEP_PADDING);
    
    //Cast back to chars for transport and printing
    char* normBuff = new char[RSA_size(rsa)];
    bzero(normBuff,RSA_size(rsa));
    for(int i = 0; i < RSA_size(rsa);i++)
    {
        normBuff[i] = static_cast<char>(encBuff[i]);
    }
    std::cout << "Encrypted 'Hello World!' " << std::endl;
    n = write(m_fd,normBuff,RSA_size(rsa));
    RSA_free(rsa);
    
    
}
int Client::GetInput()
{
    
    printf("Please enter the message: ");
    bzero(m_msgBuffer,m_msgSize);
    fgets(m_msgBuffer,m_msgSize-1,stdin);
    
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
#ifdef __linux__
int Client::Aurthorize()
{
    printf("Please enter a username: ");
    bzero(m_msgBuffer,256);
    fgets(m_msgBuffer,250,stdin);
    g_ShiftBufferRight(m_msgBuffer,256,5);
    m_msgBuffer[0] = 'c';
    m_msgBuffer[1] = 'r';
    m_msgBuffer[2] = 'e';
    m_msgBuffer[3] = 'd';
    m_msgBuffer[4] = '=';
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
#elif _WIN32
int Client::Aurthorize()
{
    return -1;
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
    /*err = c.GetInput();
    if (err != 0)
    {
        std::cout << g_GetSocketError(err) << std::endl;
        exit(1);
    }*/
    return 0;
}
