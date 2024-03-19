#include <sys/inotify.h> //inotify_init, inotify_add_watch

#include "logger_inc.hpp"
#include "dir_monitor.hpp"

namespace ilrd
{

namespace detail
{
int const fail = -1;
}//detail

DirMonitor::DirMonitor( const char *pathToMonitor, 
                        int *fd, 
                        LoggerConfigurator* loggerConfigurator, 
                        SoLoader *soLoader)
:   m_toMonitor(pathToMonitor), 
    m_notifyFd(fd), 
    m_dispatcher(), 
    m_soLoader(soLoader),
    m_loggerConfigurator(loggerConfigurator),
    m_firstTime(true)
{
    CallBackBaseDispatcher *toSendSoLoader = new CallBackDispatcher<SoLoader>(m_soLoader);
    CallBackBaseDispatcher *toSendLoggerCfg = new CallBackDispatcher<LoggerConfigurator>(m_loggerConfigurator);
    Register("soLoader", toSendSoLoader);    
    Register("loggerCfg", toSendLoggerCfg);

    if (detail::fail == (*m_notifyFd = inotify_init()))
    {
        *Logger::InstaceLogger() << Logger::ERROR << "inotify init error" 
                                        << strerror(errno)  << std::endl;
        //throw
    }
    *Logger::InstaceLogger() << Logger::INFO << "CTOR - Monitor" << std::endl;
}

void DirMonitor::WatchMonitor(int nothing)
{    
    (void)nothing;

    *Logger::InstaceLogger() << Logger::INFO << "WatchDirMonitor" << std::endl;

    if (detail::fail == inotify_add_watch(*m_notifyFd, m_toMonitor, IN_CREATE | IN_MOVED_TO))
    {
        *Logger::InstaceLogger() << Logger::ERROR << "inotify_add_watch error" 
                                        << strerror(errno)  << std::endl;
        //throw
        return;
    }
    *Logger::InstaceLogger() << Logger::INFO << "WatchDirMonitor is watching\n";
}

void DirMonitor::Register(std::string key, CallBackBaseDispatcher* toMonitor)
{
    *Logger::InstaceLogger() << Logger::INFO << "DirMonitor::Register\n";
    m_dispatcher.RegisterDispatcher(key, toMonitor);
}

void DirMonitor::UnRegister(std::string key)
{
    *Logger::InstaceLogger() << Logger::INFO << "DirMonitor::UnRegister\n";
    m_dispatcher.UnRegisterDispatcher(key);
}

void DirMonitor::Notify(int i)
{
    (void)i;

    if (m_firstTime == false)
    {
        static int const minNumToRead = sizeof(struct inotify_event) + NAME_MAX + 1;
        static char buf[minNumToRead] = {0};

        read(*m_notifyFd, (void *)buf, minNumToRead);
    }
    m_firstTime = false;
    
    std::cout << "DirMonitor::Notify" << std::endl;
    m_dispatcher.Notify();
    
}

}//ilrd

