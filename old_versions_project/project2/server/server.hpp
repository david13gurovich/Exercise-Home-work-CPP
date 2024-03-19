#ifndef H_SERVER
#define H_SERVER

#include "reactor_inc.hpp"
#include <cstring> //memcpy

namespace ilrd
{

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

class Server
{
public:
    Server(Reactor *reactor);
    //~Server = default;
    void operator()(int sockfd);
    void CreateSocket();
    int UdpSocket() { return m_udpSocket; }
    Reactor& GetReactor() { return *m_reactor; }

private:
//    Server(const Server&);
//    Server& operator=(const Server&);

    int m_udpSocket;
    int m_tcpSocket;
    int m_consoleSocket;
    Reactor *m_reactor;
};

class Socket
{
public:
    Socket(int *udpSocket);
    int CreateSocket();
private:
    int *m_udpSocket;

    static void InitServerAddr(struct sockaddr_in *server_addr);
};

class Packet
{
public:
    Packet(int type, char *uid)
    : m_Type(type)
    {
        memcpy(m_uid, uid, details::UID_BYTES);
    }

    virtual ~Packet(){}
    
    char m_Type;
    char m_uid[details::UID_BYTES];
};

}//ilrd

#endif