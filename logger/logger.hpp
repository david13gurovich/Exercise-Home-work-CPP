#ifndef ILRD_RD61_LOGGER_HPP
#define ILRD_RD61_LOGGER_HPP

#include <string> //string
#include <ostream> //ostream
#include <cstdlib>
#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp> //boost::mutex
#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/bind.hpp>

namespace ilrd
{
class Logger
{

public:
    enum Severity { ERROR = 0, WARNING = 1, INFO = 2, DEBUG = 3 };
    
    static Logger* InstaceLogger(Severity severity, std::ostream* typeDest);
    static void DestoyLogger();
    //~Logger() = defult

    std::ostream& operator<<(Severity eventSeverity);
    void IncSeverity();
    void DecSeverity();


private: 
    Severity m_severity;
    std::ostream *m_typeDest;
    std::ostream m_noOutput;
    
    static Logger *m_loggerInstance;
    static boost::mutex m_lock;

    explicit Logger(Severity severity, std::ostream* typeDest);
    Logger(const Logger&);
    Logger& operator=(const Logger&);

    void SetSeverity(int PlusMinus); 
};

}//ilrd

#endif
