#include <stdlib.h> //exit_status
#include <sys/types.h> //bind, recvfrom, sendto
#include <sys/socket.h> //socket, AF_INET, bind, recvfrom, sendto
#include <string.h> //memset
#include <arpa/inet.h> //htons
#include <unistd.h> //sleep
#include <iostream> //open, clse, write, read
#include <fstream> //open, clse, write, read

#include "logger_inc.hpp"
#include "udp_server.h"
#include "exception.hpp"

const int FAIL = -1;

namespace ilrd
{

Socket::Socket(int *udpSocket)
: m_udpSocket(udpSocket)
{}

int Socket::CreateSocket()
{
    struct sockaddr_in servaddr; 

    *m_udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (FAIL == *m_udpSocket)
    {
        *ilrd::Logger::InstaceLogger() << ilrd::Logger::ERROR << "socket failed";
        return (EXIT_FAILURE);
    }
    InitServerAddr(&servaddr);

    int opt = 1;
    if (FAIL == setsockopt(*m_udpSocket, SOL_SOCKET, 
                            SO_REUSEADDR | SO_REUSEPORT,
                            &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    if (FAIL == bind(*m_udpSocket, (const struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
       *ilrd::Logger::InstaceLogger() << ilrd::Logger::ERROR << 
                                "bind failed" << strerror(errno) <<std::endl;
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);  
}

void Socket::InitServerAddr(struct sockaddr_in *server_addr)
{
    memset(server_addr, 0, sizeof(*server_addr));

    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = INADDR_ANY;
    server_addr->sin_port = htons(details::PORT);
}

void WriteToFile(int blockIndex, char *dataToWrite)
{    
    char nameFile[20];
    strcpy(nameFile, "block");
    sprintf(nameFile + strlen(nameFile),"%u",blockIndex);
    
    std::fstream file;
    file.open(nameFile, std::fstream::out | std::fstream::trunc  | std::fstream::binary); 
    file.write(dataToWrite, details::DATA_BYTES);
    *ilrd::Logger::InstaceLogger() << ilrd::Logger::INFO << "write To File"
                                                             << std::endl;
    file.close();  
}

void ReadFromFile(int blockIndex, char *dataToRead)
{    
    char nameFile[20];
    strcpy(nameFile, "block");
    sprintf(nameFile + strlen(nameFile),"%u",blockIndex);
    
    std::fstream file;
    file.open(nameFile, std::fstream::in | std::fstream::binary); 
    file.read(dataToRead, details::DATA_BYTES);
    *ilrd::Logger::InstaceLogger() << ilrd::Logger::INFO << "read from File" 
                                                                << std::endl;
    file.close();  
}

static size_t GetBlockIndex(char *blockIndex)
{
    return be64toh(*(uint64_t*)(blockIndex));
}

int RCVfromClientRead(char *rcvMsg, int sockfd,  struct sockaddr_in* cliaddr)
{
    char buffer[details::DATA_BYTES];
     RcvFromClientRead rcvFromClient(rcvMsg + details::UID_OFFSET, 
                            rcvMsg + details::BLOCK_INDEX_OFSSET);
        
    ReadFromFile(GetBlockIndex(rcvFromClient.m_blockIndex), buffer);
    SendToClientRead toSend(rcvFromClient.m_uid, 1, buffer);

    return (sendto(sockfd, &toSend, sizeof(toSend), MSG_CONFIRM,
           (const struct sockaddr *)cliaddr, sizeof(*cliaddr)));
} 

int RCVfromClientWrite(char *rcvMsg, int sockfd,  struct sockaddr_in* cliaddr)
{
    RcvFromClientWrite rcvFromClient(rcvMsg + details::UID_OFFSET, 
                                    rcvMsg + details::BLOCK_INDEX_OFSSET,
                                    rcvMsg + details::DATA_OFFSET);
            
    WriteToFile(GetBlockIndex(rcvFromClient.m_blockIndex), rcvFromClient.m_data);
    SendToClientWrite toSend(rcvFromClient.m_uid, 1);

    return (sendto(sockfd, &toSend, sizeof(toSend), MSG_CONFIRM,
          (const struct sockaddr *)cliaddr, sizeof(*cliaddr)));
} 

}//ilrd

void SendAndRecieveUDPMinionClient(int sockfd)
{    
    char rcvMsg[details::MAXLINE];
    int status = 0;
    socklen_t len = details::MAXLINE;
    struct sockaddr_in cliaddr;
    memset(&cliaddr, 0, sizeof(cliaddr));

    int num_of_bytes = (recvfrom(sockfd, rcvMsg, details::MAXLINE, MSG_WAITALL, 
                                        (struct sockaddr *)&cliaddr, &len));
    if (FAIL == num_of_bytes)
    {
        *ilrd::Logger::InstaceLogger() << ilrd::Logger::INFO << "recvfrom failed";
        throw ilrd::RecvError();
    }

    if(WRITE == *rcvMsg)
    {
        status = ilrd::RCVfromClientWrite(rcvMsg, sockfd,  &cliaddr);
    }
    else if(READ == *rcvMsg)
    {
        status = ilrd::RCVfromClientRead(rcvMsg, sockfd,  &cliaddr);
    }
    
    if (FAIL == status)
    {
        *ilrd::Logger::InstaceLogger() << ilrd::Logger::ERROR << "sendto failed";
        throw ilrd::SendError();
    }
}

