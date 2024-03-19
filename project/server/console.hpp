#ifndef ILRD_RD61_CONSOLE_HPP
#define ILRD_RD61_CONSOLE_HPP

#include "factory.hpp"
#include "logger_inc.hpp"
#include "base_console.hpp"
#include "dervied_console.hpp"
#include "dir_monitor.hpp"

namespace ilrd
{

class Console;

class DataToFactory
{
public:
    DataToFactory(Console *console)
    : m_console(console){}
    
    Console *m_console;
};

class Console
{
public:
    explicit Console(DirMonitor *dirMonitor, 
                    LoggerConfigurator* loggerConfigurator, 
                    SoLoader *soLoader);
    
    void FuncToRegister(int);
    DirMonitor& GetDirMonitor() { return *m_dirMonitor; }
    LoggerConfigurator* GetLoggerConfig() { return m_loggerConfigurator; }
    SoLoader* GetSoLoader() { return m_soLoader; }
   
private:
    void InitFactory();
    void RegObjects();
    
    Factory <DataToFactory*, std::string, BaseConsole> m_factory;
    DirMonitor *m_dirMonitor;
    
    SoLoader *m_soLoader;
    LoggerConfigurator *m_loggerConfigurator;
};

}//ilrd

#endif

