#include <stdlib.h> //exit_status
#include <sys/types.h> //bind, recvfrom, sendto
#include <sys/socket.h> //socket, AF_INET, bind, recvfrom, sendto
#include <string.h> //memset
#include <arpa/inet.h> //htons
#include <unistd.h> //sleep
#include <iostream>
#include <fstream> //file

#include "logger_inc.hpp"
#include "exception.hpp"
#include "read_request.hpp"
#include "write_request.hpp"

const int FAIL = -1;

namespace ilrd
{

void ReadRequest::ReadFromFile(int blockIndex, char *dataToRead)
{    
    char nameFile[20];
    strcpy(nameFile, "block");
    sprintf(nameFile + strlen(nameFile),"%u",blockIndex);
    
    std::fstream file;
    file.open(nameFile, std::fstream::in | std::fstream::binary); 
    file.read(dataToRead, details::DATA_BYTES);
    file.close();  
}

static size_t GetBlockIndex(char *blockIndex)
{
    return be64toh(*(uint64_t*)(blockIndex));
}

ReadRequest::ReadRequest(char *rcvMsg, int sockfd, struct sockaddr_in* cliaddr)
    :   m_sockfd(sockfd), 
        m_cliaddr(cliaddr), 
        m_rcvFromClient(PacketRead(rcvMsg + details::UID_OFFSET, 
                                rcvMsg + details::BLOCK_INDEX_OFSSET))
{}

void ReplayRead::SendRead(int sockfd, struct sockaddr_in* cliaddr)
{
    static const int readReplySize = 4106;
    char bufferToSend[readReplySize];
    bufferToSend[0] = packet.m_Type;
    
    memcpy(bufferToSend + 1, packet.m_uid, sizeof(packet.m_uid));
    memcpy(bufferToSend + 10, m_data, details::DATA_BYTES);
    
    int status = sendto(sockfd, bufferToSend, readReplySize, MSG_CONFIRM,
          (const struct sockaddr *)cliaddr, sizeof(*cliaddr));

    if(-1 == status)
    {
        throw SendError();
    }
}

void ReadRequest::Action()
{
    char buffer[details::DATA_BYTES];
    ReadRequest::ReadFromFile(GetBlockIndex(m_rcvFromClient.m_blockIndex), buffer);
    
    ReplayRead toSend(m_rcvFromClient.m_uid, 1, buffer);
    toSend.SendRead(m_sockfd, m_cliaddr);
    
}

}//ilrd

extern "C"
{
    ilrd::Command* Create(char *rcvMsg, int sockefd, 
                                    struct sockaddr_in* cliaddr)
    {
        return new ilrd::ReadRequest(rcvMsg, sockefd, cliaddr);
    }
}

