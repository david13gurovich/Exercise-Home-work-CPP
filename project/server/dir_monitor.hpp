#ifndef _RD61_H_DIR_MONITOR
#define _RD61_H_DIR_MONITOR

#include "dispatcher.hpp"
#include "so_loader.hpp"
#include "logger_configuration.hpp"

namespace ilrd
{

class DirMonitor
{
public:
    DirMonitor( const char *pathToMonitor, 
                int *fd, 
                LoggerConfigurator* loggerConfigurator, 
                SoLoader *soLoader);
    //~DirMonitor() = defult
    
    void WatchMonitor(int nothing);
    void Register(std::string key, CallBackBaseDispatcher* toMonitor);
    void UnRegister(std::string key);
    void Notify(int);

private:
   const char *m_toMonitor;
   int *m_notifyFd;
   Dispatcher m_dispatcher;

   SoLoader *m_soLoader;
   LoggerConfigurator *m_loggerConfigurator;
   bool m_firstTime;
   
   void InitObjects();
};

}//ilrd
#endif