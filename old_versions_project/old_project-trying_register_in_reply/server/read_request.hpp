#ifndef H_READ_REQ 
#define H_READ_REQ

#include <cstring>

#include "server.hpp"
#include "common_types.hpp"
#include "command.hpp"
#include "reactor_inc.hpp"

namespace ilrd
{

class PacketRead : public Packet
{
public:
    PacketRead(char *uid, char *blockIndex)
    :   Packet(READ, uid)
    {
        memcpy(m_blockIndex, blockIndex, details::BLOCK_INDEX_BYTES);
    }
    
    char m_blockIndex[details::BLOCK_INDEX_BYTES];
};

class ReplayRead
{
public:
    ReplayRead(char *uid, 
                char status, 
                char *data, 
                struct sockaddr_in* cliaddr)
    :   packet(Packet(READ, uid)),
        m_status(status),
        m_cliaddr(cliaddr)
    {
        memcpy(m_data, data, details::DATA_BYTES);
    }

    void SendRead(int socket);
    
    Packet packet;
    char m_status;
    char m_data[details::DATA_BYTES]; 
    struct sockaddr_in* m_cliaddr;
}; 


class ReadRequest : public Command
{
public:
    ReadRequest(ilrd::Reactor *reactor, 
                char *rcvMsg, 
                int sockfd,  
                struct sockaddr_in* cliaddr);
    
    void Action();

private:
    int m_sockfd;
    struct sockaddr_in* m_cliaddr;
    PacketRead m_rcvFromClient;
    Reactor *m_reactor;
    
    static void ReadFromFile(int blockIndex, char *dataToRead);
};

}//ilrd

extern "C"
{
    ilrd::Command* Create(  ilrd::Reactor *reactor, 
                            char *rcvMsg, 
                            int sockefd, 
                            struct sockaddr_in* cliaddr);
}

#endif