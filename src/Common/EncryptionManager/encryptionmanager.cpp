#include <iostream>
#include <Common/EncryptionManager/EncryptionManager.h>

/*Server::Server()
{
    m_host = DEFAULT_HOST;
    m_port = DEFAULT_PORT;
    m_clientKey = EVP_PKEY_new();
}
void Server::m_CheckCertificate()
{
    if(fs::exists("cert.pem"))
    {
        std::cout << TERMINAL_GREEN << "Certificate Exists!" << TERMINAL_NOCOLOR << std::endl;
    }
    else
    {
        std::cout << TERMINAL_CYAN << "Generating Certificate" << TERMINAL_NOCOLOR << std::endl;
        //generate
        EVP_PKEY* key = EVP_PKEY_new();
        BIGNUM* bn = BN_new();
        BN_set_word(bn,RSA_F4);
        
        RSA* rsa = RSA_new();
        RSA_generate_key_ex(
            rsa, //RSA structure
            2048, //Bitlengh
            bn, //bn structure
            0
        );
        BN_free(bn);
        EVP_PKEY_assign_RSA(key,rsa);
        X509* x509 = X509_new();
        ASN1_INTEGER_set(X509_get_serialNumber(x509),1);
        X509_gmtime_adj(X509_get_notBefore(x509), 0);
        X509_gmtime_adj(X509_get_notAfter(x509), 31536000L);
        X509_set_pubkey(x509, key);
        X509_NAME* name = X509_get_subject_name(x509);
        X509_NAME_add_entry_by_txt(name, "C",  MBSTRING_ASC,
                           (unsigned char *)"DK", -1, -1, 0);
        X509_NAME_add_entry_by_txt(name, "O",  MBSTRING_ASC,
                           (unsigned char *)"Rosenoern Productions", -1, -1, 0);
        X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC,
                           (unsigned char *)"localhost", -1, -1, 0);
        X509_set_issuer_name(x509, name);
        X509_sign(x509, key, EVP_sha1());
        BIO* bioKey = BIO_new_file("key.pem","w");
        BIO* bioCert = BIO_new_file("cert.pem","w");
        PEM_write_bio_RSAPrivateKey(bioKey,rsa,NULL,NULL,0,NULL,NULL);
        PEM_write_bio_X509(bioCert,x509);
        EVP_PKEY_free(key);
        X509_free(x509);
        BIO_free_all(bioKey);
        BIO_free_all(bioCert);
        
    }
}

void Server::m_SetSocketTimeout(int fd, int seconds)
{
    timeval tv;
    tv.tv_sec = seconds;
    tv.tv_usec = 0;
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO,&tv, sizeof(tv));
}
std::string Server::m_GenerateToken(std::string userName)
{
    Key* cond = new Key[1];
    cond[0] = Key("username",userName);
    uint64_t results = 0;
    DBRow* rows = m_DBMan.GetRowsWhere("Users",cond,1,results);
    if(results == 0)
    {
        //Server error
        std::cout << TERMINAL_RED << "INTERNAL SERVER ERROR" << TERMINAL_NOCOLOR << std::endl;
        return "";
    }
    std::string userID = rows[0].Find("id").value;
    cond[0] = Key("userId",userID);
    delete[] rows;
    std::string token = "";
    rows = m_DBMan.GetRowsWhere("Tokens",cond,1,results);
    if(results == 0)
    {
        
    }
    else
    {
       token = rows[0].Find("token").value; 
    }
    delete[] cond;
    return token;
}

int Server::m_PrepareDB()
{
    m_DBMan = DBManager();
    if(!fs::exists("./PenguinTalkDB.sdb"))
    {
        m_DBMan.CreateDB("./PenguinTalkDB.sdb");
        m_DBMan.LoadDB("./PenguinTalkDB.sdb");
        DBColumn* columns = new DBColumn[3];
        columns[0] = DBColumn("id",INT,8,PRIMARY_KEY | NOT_NULL | AUTO_INCREMENT);
        columns[1] = DBColumn("username",VARCHAR,256,NOT_NULL);
        columns[2] = DBColumn("passhash",VARCHAR,256,NOT_NULL);
        bool res = m_DBMan.CreateTable("Users",3,columns);
        if(res == 0)
        {
            return res;
        }
        delete[] columns;
        columns = new DBColumn[3];
        columns[0] = DBColumn("id",INT,8,PRIMARY_KEY | NOT_NULL | AUTO_INCREMENT);
        columns[1] = DBColumn("userId",INT,8,NOT_NULL);
        columns[2] = DBColumn("token",VARCHAR,256,NOT_NULL);
        res = m_DBMan.CreateTable("Tokens",3,columns);
        */
        /*DBRow row = DBRow();
        row.InsertData("username","AnzoDK");
        row.InsertData("passhash","");
        m_DBMan.InsertRow("Users",row);
        //Debug
        uint64_t results = 0;
        Key* conditions = new Key[1];
        conditions[0] = Key("id","0");
        DBRow* out = m_DBMan.GetRowsWhere("Users",conditions,1,results);
        for(uint64_t i = 0; i < results; i++)
        {
            std::cout << TERMINAL_GREEN << "User: id: " << out[i].Find("id").value << " username: " << out[i].Find("username").value << " hash: " << out[i].Find("passhash").value << TERMINAL_NOCOLOR << std::endl;
        }*/
 /*       
        return res;
        
    }
    else
    {
        return m_DBMan.LoadDB("./PenguinTalkDB.sdb");
    }
}

int Server::Init(int maxThreads)
{
#ifdef _WIN32
    WORD wV = MAKEWORD(2, 2);
    WSADATA wsaData;
    WSAStartup(wV, &wsaData);
#endif
    OpenSSL_add_all_algorithms();
    OpenSSL_add_all_ciphers();
    SSL_library_init();
    SSL_load_error_strings();
    m_msgBuffer = new char[m_msgSize];
    if (m_PrepareDB() == false)
    {
        std::cout << TERMINAL_RED << "Failed to prepare DB" << std::endl;
        std::cout << m_DBMan.Error() << TERMINAL_NOCOLOR << std::endl;
        
    }
    else
    {
        std::cout << TERMINAL_GREEN << "DB Prepared!" << TERMINAL_NOCOLOR << std::endl;
    }
    m_CheckCertificate();
    m_maxThreads = maxThreads;
    std::cout << "Setting max connections to " << std::to_string(m_maxThreads) << std::endl;
    m_threadIDs = new int[m_maxThreads];
    m_fd = socket(AF_INET,SOCK_STREAM,0);
    //m_SetSocketTimeout(m_fd,15); //Wait for 15 seconds for a connection - Prob pretty bad
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
void Server::m_InitEncrypt(int responseSocket)
{
    //Load Privatekey
    BIO* pkey = BIO_new_file("./key.pem","rb");
    */
    //Load Certificate (BIO can be used for openSSL functions)
    /*BIO* pubKeyBio = *//*BIO_new_file("./cert.pem","rb");*//*BIO_new(BIO_s_mem());*/
/*    
    //Load Certificate for transport
    std::ifstream in = std::ifstream("./cert.pem", std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = in.tellg();

    std::vector<char> result(pos);

    in.seekg(0, std::ios::beg);
    in.read(&result[0], pos); //&result[0] is the same as result.data()
    in.close();
    
    BIO_puts(pubKeyBio,&result[0]);
    
    //Create RSA handler
    X509* x509 = X509_new();
    PEM_read_bio_X509(pubKeyBio,&x509,NULL,NULL);
    EVP_PKEY* pubKey = X509_get_pubkey(x509);
    EVP_PKEY* privKey = EVP_PKEY_new();
    PEM_read_bio_PrivateKey(pkey,&privKey,NULL,NULL);
    RSA* pubRsa = RSA_new();
    pubRsa = EVP_PKEY_get1_RSA(pubKey);
    RSA* privRsa = EVP_PKEY_get1_RSA(privKey);
    

    
    int n = write(responseSocket,&result[0],result.size());
    bzero(m_msgBuffer,m_msgSize);
    BIO_free_all(pkey);
    BIO_free_all(pubKeyBio);
    if(n <= 0)
    {
        std::cout << TERMINAL_RED <<"Failed to send certificate" << TERMINAL_NOCOLOR << std::endl;
        close(responseSocket);
        close(m_fd);
        exit(1);
    }
    bzero(m_msgBuffer,RSA_size(pubRsa));
    unsigned char* out = new unsigned char[RSA_size(pubRsa)];
    n = read(responseSocket,m_msgBuffer,RSA_size(pubRsa));
    if(n <= 0)
    {
        std::cout << TERMINAL_RED << "Connection Interupted" << TERMINAL_NOCOLOR << std::endl;
        close(responseSocket);
        close(m_fd);
        exit(1);
    }
    unsigned char* tmp = g_ToUnsignedBuffer(m_msgBuffer,RSA_size(pubRsa));
    
    RSA_private_decrypt(RSA_size(pubRsa),tmp,out,privRsa,RSA_PKCS1_OAEP_PADDING);
    
    char* sOut = g_ToSignedBuffer(out,RSA_size(privRsa));
    std::cout << "Decrypted: " << std::string(sOut) << std::endl;
    delete[] out;
    delete[] tmp;
    delete[] sOut;
    RSA_free(pubRsa);
    RSA_free(privRsa);
}

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
        bzero(m_msgBuffer,m_msgSize);
        int n = read(acc_socket,m_msgBuffer,m_msgSize-1);
        if(n < 0)
        {
            return SOCKET_READ_ERROR;
        }
        //close(acc_socket);
        //close(m_fd);
        std::cout << std::string(m_msgBuffer) << std::endl;
        if(std::string(g_CopyBuffer(m_msgBuffer,0,10)) == "AUTH_START")
        {
            //Await client to send auth data
            n = write(acc_socket,"CONFIRMED",9);
            bzero(m_msgBuffer,m_msgSize);
            m_SetSocketTimeout(acc_socket,15);
        
            m_InitEncrypt(acc_socket);
        
            n = read(acc_socket,m_msgBuffer,m_msgSize);
            if(n <= 0)
            {
                //Timed out
                std::cout << TERMINAL_YELLOW << "Timed out" << TERMINAL_NOCOLOR << std::endl;
                close(acc_socket);
                close(m_fd);
                exit(1);
            }
            std::string recvString = std::string(m_msgBuffer,n);
            bzero(m_msgBuffer,m_msgSize);
            JsonHandler json = JsonHandler(recvString);
            if(!json.Process())
            {
                std::cout << TERMINAL_RED << "Invalid Json Recvieved" << TERMINAL_NOCOLOR << std::endl;
                close(acc_socket);
            }
            else
            {
                std::string hash = "";
                Key* cond = new Key[1];
                cond[0] = Key("username",json.GetVariable("user"));
                uint64_t results = 0;
                DBRow* r = m_DBMan.GetRowsWhere("Users",cond,1,results);
                if(results!=0)
                {
                    hash = r[0].Find("passhash").value;
                }
                else
                {
                    //invalid user
                    std::string mes = "Invalid User";
                    write(acc_socket, mes.c_str(),mes.length());
                    close(acc_socket);
                }
            delete[] cond;
            if(hash == json.GetVariable("hash"))
            {
                //Auth!
                std::string mes = "OK";
                write(acc_socket,mes.c_str(),mes.length());
                std::string token = m_GenerateToken(json.GetVariable("user"));
                std::string jsonMsg = "{\"AuthToken\":\"";
                jsonMsg += token;
                jsonMsg += "\"";
                write(acc_socket, jsonMsg.c_str(),jsonMsg.length());
              
            }
            else
            {
                std::string mes = "Invalid User";
                write(acc_socket, mes.c_str(),mes.length());
                close(acc_socket);
              
            }
          
            }
        
        }
    }
    return NO_ERROR;
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
    return NO_ERROR;
}
#endif
*/

