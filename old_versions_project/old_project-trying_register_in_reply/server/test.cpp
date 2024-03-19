#include <stdlib.h> //exit_status
#include <sys/types.h> //bind, recvfrom, sendto
#include <sys/socket.h> //socket, AF_INET, bind, recvfrom, sendto
#include <string.h> //memset
#include <arpa/inet.h> //htons
#include <unistd.h> //sleep
#include <iostream>
#include <fstream> //file

#include "test.hpp"

namespace ilrd
{
void ReplayRead::SendRead(int sockfd, struct sockaddr_in* cliaddr)
{
    static const int readReplySize = 4106;
    char bufferToSend[readReplySize];
    bufferToSend[0] = packet.m_Type;
    
    memcpy(bufferToSend + 1, packet.m_uid, sizeof(packet.m_uid));
    memcpy(bufferToSend + 10, m_data, details::DATA_BYTES);
    
    int status = sendto(sockfd, bufferToSend, readReplySize, MSG_CONFIRM,
          (const struct sockaddr *)cliaddr, sizeof(*cliaddr));
}

static size_t GetBlockIndex(char *blockIndex)
{
    return be64toh(*(uint64_t*)(blockIndex));
}

void ReadRequest::Action()
{
    char buffer[details::DATA_BYTES];
    ReadRequest::ReadFromFile(GetBlockIndex(m_rcvFromClient.m_blockIndex), buffer);
    
    ReplayRead toSend(m_rcvFromClient.m_uid, 1, buffer);
    toSend.SendRead(m_sockfd, m_cliaddr);
    
}

}//ilrd

ilrd::Command* CreateReadRequest(char *rcvMsg, int sockefd, 
                                struct sockaddr_in* cliaddr)
{
    return new ilrd::ReadRequest(rcvMsg, sockefd, cliaddr);
}


