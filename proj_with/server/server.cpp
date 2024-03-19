#include <iostream> //std::cout
#include <stdlib.h>//exit_status
#include <assert.h> //assert
#include <sys/socket.h> //socket
#include <string.h> // streror, strncmp, strlen
#include <stdio.h> //stdin, print, perror
#include <unistd.h> //STDIN_FILENO, read
#include <dlfcn.h> //dlopen, dlsym, dlclose

#include <arpa/inet.h>  
#include <pthread.h> 
#include <signal.h> 

#include "logger_inc.hpp"
#include "console.h"
#include "tcp_server.h"
#include "read_request.hpp"
#include "write_request.hpp"
#include "scan_folder.hpp"

namespace detail
{
static const int fail = -1;
static const char libCommandWrite[] = "../infrastructure/lib/libCommandWrite.so";
static const char libCommandRead[] = "../infrastructure/lib/libCommandRead.so";
static const char createFunc[] = "Create";
static const char *pathLibDir = "../infrastructure/lib/";
enum libInDir {WRITE, READ};
}

namespace ilrd
{

CommandSharedPtr (*createCommandRead)(CreateFuncData& data);
CommandSharedPtr (*createCommandWrite)(CreateFuncData& data);

Server::Server(Reactor *reactor)
:   m_udpSocket(-1),
    m_tcpSocket(-1),
    m_consoleSocket(-1),
    m_reactor(reactor)
{}

void Server::CreateSocket()
{
    Socket newSocket(&m_udpSocket);
    newSocket.CreateSocket();
}

void Server::operator()(int sockfd)
{
    char rcvMsg[details::MSG_TOTAL_BYTES];
    int status = 0;
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    memset(&cliaddr, 0, sizeof(cliaddr));

    int num_of_bytes = (recvfrom(sockfd, rcvMsg, details::MSG_TOTAL_BYTES, MSG_WAITALL, 
                                        (struct sockaddr *)&cliaddr, &len));
    if (detail::fail == num_of_bytes)
    {
        *Logger::InstaceLogger() << Logger::INFO << "recvfrom failed";
        throw RecvError();
    }

    Server::InitLibraries(rcvMsg, sockfd, &cliaddr);
    //DATA: ilrd::CreateFuncData &data
    //Product: Command
    //Identifier: char
    
    if(WRITE == *rcvMsg)
    {
        m_requestMsgWrite->Action();
    }
    else if(READ == *rcvMsg)
    {
        m_requestMsgRead->Action();
    }
    
    if (detail::fail == status)
    {
        *Logger::InstaceLogger() << Logger::ERROR << "sendto failed";
        throw SendError();
    }

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
    
    if (detail::fail == bind(*m_udpSocket, (const struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
       *Logger::InstaceLogger() << Logger::ERROR << 
                                "bind failed" << strerror(errno) <<std::endl;
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);  
}

void Server::InitLibraries(char *reqMsg, int sockfd, struct sockaddr_in *cliaddr)
{
    ScanFolder scanFolder(detail::pathLibDir);
    char **libNames = scanFolder.SoLibraries();
    static const size_t soLibrariesCnt = scanFolder.GetSoLibrariesCnt();
    
    void *nameHandler[soLibrariesCnt];
    for (size_t i = 0; i < soLibrariesCnt; ++i)
    {
        nameHandler[i] = dlopen(libNames[i],  RTLD_LAZY);
        if(NULL == nameHandler[i])
        {
            *Logger::InstaceLogger() << Logger::ERROR << "dlopen failed";
            //throw!
        }
    }
    
    *(void **)(&createCommandRead) = dlsym(nameHandler[detail::READ], detail::createFunc);
    *(void **)(&createCommandWrite) = dlsym(nameHandler[detail::WRITE], detail::createFunc);
    
    CreateFuncData data(reqMsg, sockfd, cliaddr, NULL);
    if (createCommandWrite && createCommandRead) 
    {
        m_requestMsgRead = createCommandRead(data);
        m_requestMsgWrite = createCommandWrite(data);
    }
    else
    {
        *Logger::InstaceLogger() << Logger::ERROR << "dlsym failed";
        //throw
    }
}

}//ilrd

int main()
{
    ilrd::Logger *logInstance = ilrd::Logger::InstaceLogger();
    ilrd::Reactor reactor;

    ilrd::Server server(&reactor);
    server.CreateSocket();
    
    //not object orinted
    int tcp_socket = 0;
    struct sockaddr_in server_addr;
    if (EXIT_FAILURE == CreateTcpServerAndBind(logInstance, &tcp_socket, &server_addr))
    {
        return (EXIT_FAILURE);
    } 
    FunctorToPassReactor functorToPass(&server_addr, tcp_socket, &reactor);
    server.GetReactor().Register(tcp_socket, functorToPass, READ);
    ilrd::Console console;
    server.GetReactor().Register(STDIN_FILENO, &console, &ilrd::Console::FuncToRegister, READ);
    
    //object orinted
    server.GetReactor().Register(server.UdpSocket(), server, READ);    
    reactor.StartEventLoop();

    return (EXIT_SUCCESS);
} 

