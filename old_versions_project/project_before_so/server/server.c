#include <iostream> //std::cout
#include <stdlib.h>//exit_status
#include <assert.h> //assert
#include <sys/socket.h> //socket
#include <string.h> // streror, strncmp, strlen
#include <stdio.h> //stdin, print, perror
#include <unistd.h> //STDIN_FILENO, read

#include <arpa/inet.h>  
#include <pthread.h> 
#include <signal.h> 

#include "reactor_inc.hpp"
#include "logger_inc.hpp"
#include "common_types.hpp"
#include "console.h"
#include "udp_server.h"
#include "tcp_server.h"

int main()
{
    ilrd::Logger *logInstance = ilrd::Logger::InstaceLogger();
    ilrd::Reactor reactor;
        
    int udpSocket = 0;
    ilrd::Socket udpServer(&udpSocket);
    if(EXIT_FAILURE == udpServer.CreateSocket())
    {
        return (EXIT_FAILURE);
    }
    
    int tcp_socket = 0;
    struct sockaddr_in server_addr;
    if (EXIT_FAILURE == CreateTcpServerAndBind(logInstance, &tcp_socket, &server_addr))
    {
        return (EXIT_FAILURE);
    } 
    FunctorToPassReactor functorToPass(&server_addr, tcp_socket, &reactor);
    reactor.Register(tcp_socket, functorToPass, READ);

    ilrd::Console console;
    reactor.Register(STDIN_FILENO, &console, &ilrd::Console::FuncToRegister, READ);
    reactor.Register(udpSocket, RECEIVER, READ);
    reactor.Register(udpSocket, REPLIER, WRITE);
    
    reactor.StartEventLoop();

    return (EXIT_SUCCESS);
}
