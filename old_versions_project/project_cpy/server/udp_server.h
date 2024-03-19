#ifndef H_UDP_SERVER_ 
#define H_UDP_SERVER_
/**************************************************/
/* this file define server udp */
/**************************************************/

#include <sys/socket.h> //struct sockaddr_in

#include "common_types.hpp"

int CreateUdpServerAndBind(int *udp_socket);
void SendAndRecieveUDP(int sockfd);
void SendAndRecieveUDPMinionClient(int sockfd);

namespace details 
{
int const DATA_BYTES = 4096;
int const MSG_TOTAL_BYTES = 4113;
int const BLOCK_INDEX_BYTES = 8;
int const UID_BYTES = 8;
int const PORT = 8080;
int const MAXLINE = 8000;
int const UID_OFFSET = 1;
int const BLOCK_INDEX_OFSSET = 9;
int const DATA_OFFSET = 17;
}//detail

namespace ilrd
{
class Socket
{
public:
    Socket(int *udpSocket);
    int CreateSocket();
private:
    int *m_udpSocket;

    static void InitServerAddr(struct sockaddr_in *server_addr);
};

class SendAndRecieveBase
{
public:
    SendAndRecieveBase(int type, char *uid)
    : m_Type(type)
    {
        memcpy(m_uid, uid, details::UID_BYTES);
    }
    
    char m_Type;
    char m_uid[details::UID_BYTES];
};

class RcvFromClientRead : public SendAndRecieveBase
{
public:
    RcvFromClientRead(char *uid, char *blockIndex)
    :   SendAndRecieveBase(READ, uid)
    {
        memcpy(m_blockIndex, blockIndex, details::BLOCK_INDEX_BYTES);
    }
    
    char m_blockIndex[details::BLOCK_INDEX_BYTES];
};

class RcvFromClientWrite : public SendAndRecieveBase
{
public:
    RcvFromClientWrite(char *uid, char *blockIndex, char *data)
    :   SendAndRecieveBase(WRITE, uid)
    {
        memcpy(m_blockIndex, blockIndex, details::BLOCK_INDEX_BYTES);
        memcpy(m_data, data, details::DATA_BYTES);
    }
    char m_blockIndex[details::BLOCK_INDEX_BYTES];
    char m_data[details::DATA_BYTES]; 
};

class SendToClientRead : public SendAndRecieveBase
{
public:
    SendToClientRead(char *uid, char status, char *data)
    :   SendAndRecieveBase(READ, uid),
        m_status(status)
    {
        memcpy(m_data, data, details::DATA_BYTES);
    }
    
    char m_status;
    char m_data[details::DATA_BYTES]; 
}; 

class SendToClientWrite : public SendAndRecieveBase
{
public:
    SendToClientWrite(char *uid, char status)
    :   SendAndRecieveBase(WRITE, uid),
        m_status(status){}
    
    char m_status;
}; 

int RCVfromClientRead(char *rcvMsg, int sockfd,  struct sockaddr_in* cliaddr);
int RCVfromClientWrite(char *rcvMsg, int sockfd,  struct sockaddr_in* cliaddr);
void ReadFromFile(int blockIndex, char *dataToRead);
void WriteToFile(int blockIndex, char *dataToWrite);

}//ilrd

#endif