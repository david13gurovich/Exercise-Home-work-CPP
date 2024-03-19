#include <iostream> //cout

#include "logger.hpp"

namespace ilrd
{
Logger* Logger::m_loggerInstance = NULL;
boost::mutex Logger::m_lock;

Logger* Logger::InstaceLogger(Severity severity, std::ostream* typeDest)
{
    Logger* tmp = m_loggerInstance;
    boost::atomic_thread_fence(boost::memory_order_acquire);
    if(!tmp)
    {
        boost::mutex::scoped_lock guard(m_lock);
        if(!tmp)
        {
            tmp = new Logger(severity, typeDest);
            atexit(DestoyLogger);
            boost::atomic_thread_fence(boost::memory_order_release);
            m_loggerInstance = tmp;
        }
    }

    return (tmp);
}

void Logger::DestoyLogger()
{
    delete m_loggerInstance;
}

Logger::Logger(Logger::Severity severity, std::ostream* typeDest)
:   m_severity(severity), 
    m_typeDest(typeDest),
    m_noOutput(0)
{}

std::ostream& Logger::operator<<(Severity eventSeverity)
{
    m_lock.lock();
    Severity currentSeverity = m_severity;
    m_lock.unlock();
    
    if (eventSeverity <= currentSeverity)
    { 
        boost::mutex::scoped_lock guard(m_lock);
        *m_typeDest << __TIMESTAMP__ << ", Severity: " << eventSeverity << ": ";
        
        return (*m_typeDest);
    }

    return (m_noOutput);
}
void Logger::SetSeverity(int PlusMinus)
{
    boost::mutex::scoped_lock guard(m_lock);
    int newSeverity = static_cast<int>(m_severity);
    newSeverity = (newSeverity + PlusMinus)  % 4;
    m_severity = static_cast<Severity>(newSeverity);
}

void Logger::IncSeverity()
{
   SetSeverity(+1); 
}

void Logger::DecSeverity()
{
   SetSeverity(-1);     
}

}// irld
