#ifndef H_WRITE_REQ 
#define H_WRITE_REQ

#include <cstring>

#include "common_types.hpp" //WRITE, packet
#include "command.hpp"
#include "server.hpp" //packet, details

namespace ilrd
{

class PacketWrite : public Packet
{
public:
    PacketWrite(char *uid, char *blockIndex, char *data)
    :   Packet(WRITE, uid)
    {
        memcpy(m_blockIndex, blockIndex, details::BLOCK_INDEX_BYTES);
        memcpy(m_data, data, details::DATA_BYTES);
    }
    virtual ~PacketWrite(){}
    
    char m_blockIndex[details::BLOCK_INDEX_BYTES];
    char m_data[details::DATA_BYTES]; 
};

class ReplayWrite
{
public:
    ReplayWrite(char *uid, char status, struct sockaddr_in* cliaddr)
    :   packet(Packet(WRITE, uid)),
        m_status(status),
        m_cliaddr(cliaddr)
        {}
    
    void SendWrite(int sockfd);
    
    Packet packet;
    char m_status;
    struct sockaddr_in* m_cliaddr;
}; 

class WriteRequest : public Command 
{
public:
    WriteRequest(Reactor *reactor, char *rcvMsg);
    virtual ~WriteRequest(){}
    
    void Action(int sockfd,struct sockaddr_in *cliaddr);

private:
    PacketWrite m_rcvFromClient;
    
    static void WriteToFile(int blockIndex, char *dataToWrite);
};

}//ilrd

extern "C"
{
    ilrd::CommandSharedPtr Create(ilrd::CreateFuncData &data);
    
    char GetKey() { return WRITE; }
}

#endif