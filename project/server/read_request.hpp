#ifndef H_READ_REQ 
#define H_READ_REQ

#include <cstring>

#include "server.hpp"
#include "common_types.hpp"
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

    virtual ~PacketRead(){}
    
    char m_blockIndex[details::BLOCK_INDEX_BYTES];
};

class ReplayRead
{
public:
    ReplayRead(char *uid, char status, char *data, struct sockaddr_in* cliaddr)
    :   packet(Packet(READ, uid)),
        m_status(status),
        m_cliaddr(cliaddr)
    {
        memcpy(m_data, data, details::DATA_BYTES);
    }

    void SendRead(int socket);
    
    Packet packet;
    char m_status;
    struct sockaddr_in* m_cliaddr;
    char m_data[details::DATA_BYTES]; 
}; 

class ReadRequest : public Command
{
public:
    ReadRequest(Reactor *reactor, char *rcvMsg);
    ~ReadRequest(){}
    
    void Action(int sockfd,struct sockaddr_in *cliaddr);

private:
    PacketRead m_rcvFromClient;
    
    static void ReadFromFile(int blockIndex, char *dataToRead);
};

}//ilrd

extern "C"
{
    ilrd::CommandSharedPtr Create(ilrd::CreateFuncData &data);
    
    char GetKey() { return READ; }
}

#endif