#include <iostream> //std::cout
#include <stdlib.h>//exit_status
#include <assert.h> //assert
#include <sys/socket.h> //socket
#include <string.h> // streror, strncmp, strlen
#include <stdio.h> //stdin, print, perror
#include <unistd.h> //STDIN_FILENO, read
#include <dlfcn.h> //dlopen, dlsym, dlclose
#include <sys/inotify.h>//struct inotify_event

#include "server.hpp"
#include "logger_inc.hpp"
#include "console.hpp"
#include "tcp_server.h"
#include "so_loader.hpp"

namespace detail
{
static const int fail = -1;
static const char libCommandWrite[] = "./commands/libCommandWrite.so";
static const char libCommandRead[] = "./commands/libCommandRead.so";
static const char keyFunc[] = "GetKey";
static const char *pathLibDir = "./commands/";
}

namespace ilrd
{

Server::Server(Reactor *reactor)
:   m_udpSocket(-1),
    m_tcpSocket(-1),
    m_consoleSocket(-1),
    m_reactor(reactor),
    m_compressor()
{
    LoadLibs(0);  
}

void Server::LoadLibs(int fd)
{
    (void)fd;
    SoLoader scanFolder(detail::pathLibDir, &m_msgType);
    *Logger::InstaceLogger() << Logger::INFO << "server::LoadLibs - before onNotofy\n";
    scanFolder.OnNotify(); 
    *Logger::InstaceLogger() << Logger::INFO << "server::LoadLibs - after onNotofy\n";
} 

void Server::CreateSocket()
{
    Socket newSocket(&m_udpSocket);
    newSocket.CreateSocket();
}

void Server::operator()(int sockfd)
{
    *Logger::InstaceLogger() << Logger::INFO << "operator()\n";
    char rcvMsg[details::MSG_TOTAL_BYTES];
    struct sockaddr_in cliaddr;
    memset(&cliaddr, 0, sizeof(cliaddr));
    socklen_t len = sizeof(cliaddr);

    int num_of_bytes = (recvfrom(sockfd, rcvMsg, details::MSG_TOTAL_BYTES, 
                        MSG_WAITALL, (struct sockaddr *)&cliaddr, &len));
    
    *Logger::InstaceLogger() << Logger::INFO << "recvfrom\n";
    if (detail::fail == num_of_bytes)
    {
        *Logger::InstaceLogger() << Logger::ERROR << "recvfrom failed";
        throw RecvError();
    }
    
    size_t bytesMsg = details::PACKET_WRITE_SIZE_RCV;
    if(*rcvMsg == READ)
    {
        bytesMsg = details::PACKET_READ_SIZE_RCV;
    }
    
    m_compressor.Compress(rcvMsg, bytesMsg);
    printf("****************************\n");
    printf("rcvMsg, type is: %d\n", *rcvMsg);
    printf("****************************\n");

    CreateFuncData data(rcvMsg, m_reactor);    
    CommandSharedPtr m_requestMsg = m_msgType.Create(*rcvMsg, data);
    
    m_requestMsg->Action(sockfd, &cliaddr); 
    *Logger::InstaceLogger() << Logger::INFO << "Action\n";

    //deletes!!
}

Socket::Socket(int *udpSocket)
: m_udpSocket(udpSocket)
{}

void Socket::InitServerAddr(struct sockaddr_in *server_addr)
{
    memset(server_addr, 0, sizeof(*server_addr));

    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = INADDR_ANY;
    server_addr->sin_port = htons(details::PORT);
}

int Socket::CreateSocket()
{
    struct sockaddr_in servaddr; 

    *m_udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (detail::fail == *m_udpSocket)
    {
        *Logger::InstaceLogger() << Logger::ERROR << "socket failed";
        return (EXIT_FAILURE);
    }
    InitServerAddr(&servaddr);

    int opt = 1;
    if (detail::fail == setsockopt(*m_udpSocket, SOL_SOCKET, 
                            SO_REUSEADDR | SO_REUSEPORT,
                            &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    if (detail::fail == bind(*m_udpSocket, (const struct sockaddr *)&servaddr, 
                                                            sizeof(servaddr)))
    {
       *Logger::InstaceLogger() << Logger::ERROR << 
                                "bind failed" << strerror(errno) <<std::endl;
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);  
}

}//ilrd