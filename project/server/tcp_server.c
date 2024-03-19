#include <arpa/inet.h>  //htons
#include <stdio.h>  // print, perror
#include <stdlib.h> // exit status 
#include <string.h> // strlen 
#include <sys/socket.h> //socket
#include <unistd.h> // read, sleep
#include <pthread.h> //pthread create, pthread_join
#include <signal.h> //sigaction
#include <assert.h> //assert
#include <errno.h> 

#include "common_types.hpp"
#include "tcp_server.h"
#include "logger_inc.hpp"

#define PORT 8070
#define MY_IP "127.0.0.1"
#define MAXLINE 1024
#define SIZE_ARR_CLIENTS 10

const int FAIL = -1;

void FunctorToPassReactor::RecieveAndSend(int socket_descriptor)
{
    ilrd::Logger *log = ilrd::Logger::InstaceLogger();
    char buffer_to_read[MAXLINE];
    const char *msg = "from server TCP";

    int valread = recv(socket_descriptor, buffer_to_read, MAXLINE, 0);
    if (FAIL == valread)
    {
        *log << ilrd::Logger::ERROR << "recv failed" << std::endl;
        return;
    }
    
    if (0 == valread)
    {
        m_reactor->UnRegister(socket_descriptor, READ);
        return;
    }

    buffer_to_read[valread] = '\0';
    printf("%s\n", buffer_to_read);
    
    valread = send(socket_descriptor, msg, strlen(msg) + 1, MSG_NOSIGNAL);
    if (FAIL == valread)
    {
        *log << ilrd::Logger::ERROR << "send failed" << std::endl;
        return;
    }
}

FunctorToPassReactor::FunctorToPassReactor(struct sockaddr_in *server_addr, 
                                                        int master_socket, 
                                                    ilrd::Reactor *reactor)
:   m_server_addr(server_addr),
    m_master_socket(master_socket),
    m_reactor(reactor)
{}

void FunctorToPassReactor::operator()(int fd)
{
    (void)fd;
    int new_socket;
    socklen_t addrlen = {0}; 
    ilrd::Logger *log = ilrd::Logger::InstaceLogger();
    
    new_socket = accept(m_master_socket, (struct sockaddr *)m_server_addr,
                                                                &addrlen);
    if (-1 == new_socket)
    {
        *log << ilrd::Logger::ERROR << "accept failed" << strerror(errno);
        return;
    }

    *log << ilrd::Logger::INFO << "accept client request\n";

    m_reactor->Register(new_socket, this ,&FunctorToPassReactor::RecieveAndSend, 
                                                                            READ);
}

static void InitTCPServerAddr(struct sockaddr_in *server_addr)
{
    memset(server_addr, 0, sizeof(*server_addr));

    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = INADDR_ANY;
    server_addr->sin_port = htons(PORT);
}

static int CreateMasterSocket(ilrd::Logger *log)
{
    int master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (FAIL == master_socket)
    {
        *log << ilrd::Logger::ERROR << "socket failed";
        return (FAIL);
    }

    int opt = 1;
    if (FAIL == setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                            &opt, sizeof(opt)))
    {
        *log << ilrd::Logger::ERROR << "setsockopt";
        return (FAIL);
    }

    return (master_socket);
}

int CreateTcpServerAndBind(ilrd::Logger *log, int *tcp_socket, 
                            struct sockaddr_in *server_addr)
{  
    *tcp_socket = CreateMasterSocket(log);
    if (FAIL == *tcp_socket)
    {
        return (EXIT_FAILURE);
    }

    InitTCPServerAddr(server_addr);
   
    if (FAIL == bind(*tcp_socket, (struct sockaddr *)server_addr, 
                                            sizeof(*server_addr)))
    {
        *log << ilrd::Logger::ERROR << "bind failed";
        return (EXIT_FAILURE);
    }

    if (FAIL == listen(*tcp_socket, 3))
    {
        *log << ilrd::Logger::ERROR << "listen failed";
        return (EXIT_FAILURE);
    }
          
    return (EXIT_SUCCESS); 
} 
