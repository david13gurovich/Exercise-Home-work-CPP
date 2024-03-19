#ifndef ILRD_RD61_LOGGER_CFG_HPP
#define ILRD_RD61_LOGGER_CFG_HPP

#include <string>
#include <ostream> //ostream

namespace ilrd
{

class LoggerConfigurator
{
public:
    LoggerConfigurator(std::string filePathWithLogFilePath);
    //~LoggerConfigurator() = defult
    
    virtual void OnNotify();

private:
    std::string m_pathToFile;
    std::string newConfiguration;

    std::ostream* PathToLog();
};

}//ilrd

#endif