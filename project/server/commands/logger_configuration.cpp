#include <fstream> //file
#include <sys/inotify.h>//struct inotify_event

#include "logger_configuration.hpp"
#include "logger_inc.hpp"

namespace ilrd
{

LoggerConfigurator::LoggerConfigurator(std::string pathToFile)
: m_pathToFile(pathToFile)
{}

std::ostream* LoggerConfigurator::PathToLog()
{
    std::fstream logPath;
    
    logPath.open(m_pathToFile.c_str()); 
    logPath >> newConfiguration;
    
    std::fstream *logFile = new std::fstream();
    logFile->open(newConfiguration.c_str());

    logPath.close();  
    //need to be free
    
    return logFile;
}

void LoggerConfigurator::OnNotify()
{
    std::cout << "LoggerConfigurator::OnNotify" << std::endl;
    (Logger::InstaceLogger())->SetLogFile(PathToLog());
    std::cout << "LoggerConfigurator::OnNotify - end" << std::endl;
}

}//ilrd

