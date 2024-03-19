#ifndef H_READ_REQ 
#define H_READ_REQ

#include <iostream>

#include "common_types.hpp"
#include "server.hpp"
#include "command.hpp"

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
    ReplayRead(char *uid, char status, char *data)
    :   packet(Packet(READ, uid)),
        m_status(status)
    {
        memcpy(m_data, data, details::DATA_BYTES);
    }

    void SendRead(int socket, struct sockaddr_in* cliaddr);
    
    Packet packet;
    char m_status;
    char m_data[details::DATA_BYTES]; 
}; 

class ReadRequest : public Command
{
public:
    ReadRequest(char *rcvMsg, int sockfd,  struct sockaddr_in* cliaddr)
    :   m_sockfd(sockfd), 
        m_cliaddr(cliaddr), 
        m_rcvFromClient(PacketRead(rcvMsg + details::UID_OFFSET, 
                                rcvMsg + details::BLOCK_INDEX_OFSSET))
    {}
    
    void Action();

private:
    int m_sockfd;
    struct sockaddr_in* m_cliaddr;
    PacketRead m_rcvFromClient;
    
    static void ReadFromFile(int blockIndex, char *dataToRead);
};

}//ilrd

extern "C"
{
    ilrd::Command* CreateReadRequest(char *rcvMsg, int sockefd, struct sockaddr_in* cliaddr);
}

#endif