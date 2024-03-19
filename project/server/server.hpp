#ifndef H_SERVER
#define H_SERVER

#include <cstring> //memcpy

#include "factory.hpp" //Factory
#include "reactor_inc.hpp" //Reactor
#include "command.hpp" //CommandSharedPtr
#include "create_func_data.hpp"
#include "compressor.hpp"
#include "common_types.hpp"

namespace ilrd
{
class Server
{
public:
    typedef char (*m_key)();
public:
    Server(Reactor *reactor);
    // Server(const Server&)= default;
    // Server& operator=(const Server&) = default;
    //~Server = default;
    void operator()(int sockfd);

    int UdpSocket() { return m_udpSocket; }
    static ilrd::CommandSharedPtr CreateType(CreateFuncData data);
    void CreateSocket();
    void LoadLibs(int fd);

private:
    int m_udpSocket;
    int m_tcpSocket;
    int m_consoleSocket;
    int m_loadFirstTime; 
    
    Reactor *m_reactor;
    Factory <CreateFuncData&, char, Command> m_msgType;
    Compressor m_compressor;
};

class Socket
{
public:
    Socket(int *udpSocket);
    int CreateSocket();
    int GetUdpSocket() { return *m_udpSocket; }
private:
    int *m_udpSocket;

    static void InitServerAddr(struct sockaddr_in *server_addr);
};
}//ilrd

#endif