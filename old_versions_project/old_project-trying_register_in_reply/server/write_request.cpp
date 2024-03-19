#include <iostream> //fstream
#include <fstream> //fstream

#include <stdlib.h> //exit_status
#include <sys/types.h> //bind, recvfrom, sendto
#include <sys/socket.h> //socket, AF_INET, bind, recvfrom, sendto
#include <string.h> //memset
#include <arpa/inet.h> //htons
#include <unistd.h> //sleep
#include <iostream>
#include <fstream> //file

#include "write_request.hpp"
#include "exception.hpp"

namespace ilrd
{

void WriteRequest::WriteToFile(int blockIndex, char *dataToWrite)
{    
    char nameFile[20];
    strcpy(nameFile, "block");
    sprintf(nameFile + strlen(nameFile),"%u",blockIndex);
    
    std::fstream file;
    file.open(nameFile, std::fstream::out | std::fstream::trunc  | std::fstream::binary); 
    file.write(dataToWrite, details::DATA_BYTES);
    file.close();  
}

WriteRequest::WriteRequest( Reactor *reactor, 
                            char *rcvMsg, 
                            int sockfd, 
                            struct sockaddr_in* cliaddr)
    :   m_sockfd(sockfd), 
        m_cliaddr(cliaddr), 
        m_rcvFromClient(PacketWrite(rcvMsg + details::UID_OFFSET, 
                                    rcvMsg + details::BLOCK_INDEX_OFSSET,
                                    rcvMsg + details::DATA_OFFSET)),
        m_reactor(reactor)
{}

static size_t BlockIndex(char *blockIndex)
{
    return be64toh(*(uint64_t*)(blockIndex));
}

void ReplayWrite::SendWrite(int sockfd)
{
    static const int writeReplySize = 10;
    char bufferToSend[writeReplySize];
    bufferToSend[0] = packet.m_Type;
    memcpy(bufferToSend + 1, packet.m_uid, sizeof(packet.m_uid));
    
    int status = sendto(sockfd, bufferToSend, writeReplySize, MSG_CONFIRM,
          (const struct sockaddr *)m_cliaddr, sizeof(*m_cliaddr));
    
    if(status == -1)
    {
        throw SendError();
    }
}

void WriteRequest::Action()
{
    WriteRequest::WriteToFile(BlockIndex(m_rcvFromClient.m_blockIndex), m_rcvFromClient.m_data);
    ReplayWrite toSend(m_rcvFromClient.m_uid, 1, m_cliaddr);
    
    //m_reactor->Register(m_sockfd, &toSend, );
    
    toSend.SendWrite(m_sockfd);
} 
}//ilrd

ilrd::Command* Create(  ilrd::Reactor *reactor, 
                        char *rcvMsg, 
                        int sockefd, 
                        struct sockaddr_in* cliaddr)
{
    return (new ilrd::WriteRequest(reactor, rcvMsg, sockefd, cliaddr));
}
