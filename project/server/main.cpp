#include "server.hpp"
#include "logger_inc.hpp"
#include "console.hpp"
#include "tcp_server.h"
#include "dir_monitor.hpp"
#include "logger_configuration.hpp"
#include "minion.hpp"
#include "so_loader.hpp"
#include "factory.hpp"

#include "compressor.hpp"

namespace detail
{
char const *pathLibDir = "./commands/";
const char *pathLogFile = "./commands/logger.cgf";
}

namespace ilrd
{
void Minion::SetUp()
{
    Logger *logInstance = Logger::InstaceLogger();     
    LoggerConfigurator configurator(detail::pathLogFile); 

    Factory <CreateFuncData&, char, Command> factorySoLoader;
    SoLoader soLoader(detail::pathLibDir, &factorySoLoader);
    
    int fdDirMonitor = 0;
    DirMonitor dirMonitor(detail::pathLibDir, &fdDirMonitor, &configurator, &soLoader);
    dirMonitor.WatchMonitor(0);
    
    Reactor reactor;
    Server server(&reactor);
    server.CreateSocket();

    reactor.Register(fdDirMonitor, &dirMonitor, &DirMonitor::Notify, READ);
    
    //todo: not object orinted
    int tcp_socket = 0;
    struct sockaddr_in server_addr;
    if (EXIT_FAILURE == CreateTcpServerAndBind(logInstance, &tcp_socket, &server_addr))
    {
        return;
    } 
    
    FunctorToPassReactor functorToPass(&server_addr, tcp_socket, &reactor);
    reactor.Register(tcp_socket, functorToPass, READ);
    
    Console console(&dirMonitor, &configurator, &soLoader);
    reactor.Register(STDIN_FILENO, &console, &Console::FuncToRegister, READ);
    
    reactor.Register(server.UdpSocket(), server, READ); 
    reactor.StartEventLoop(); 
}
}//ilrd

int main()
{
    ilrd::Minion minion;
    minion.SetUp();

    
/*     ilrd::Compressor compressor;
    char uid[8] = "1234567";
    ilrd::Packet toCompress(READ, uid);
    
    compressor.Compress(&toCompress, sizeof(ilrd::Packet));
    std::cout << toCompress.m_uid << std::endl;

    compressor.UnCompress(&toCompress, sizeof(ilrd::Packet), sizeof(ilrd::Packet));
    
    std::cout << toCompress.m_uid << std::endl; */
    
    return (EXIT_SUCCESS);
} 
