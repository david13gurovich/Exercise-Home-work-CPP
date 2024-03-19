#ifndef ILRD_RD61_DERIVED_CONSOLE_HPP
#define ILRD_RD61_DERIVED_CONSOLE_HPP

#include <iostream>

#include "base_console.hpp"

namespace ilrd
{

class ExitFromProg : public BaseConsole
{
public:
    virtual void Action(int)
    {
        //need to exit properly 
        exit(0); 
    }
};

class Pong : public BaseConsole
{
public:
    virtual void Action(int)
    {
        std::cout << "Pong" << std::endl;
    }
};

class IncSeverity : public BaseConsole
{
public:
    virtual void Action(int)
    {
        Logger* m_logInstance = Logger::InstaceLogger();
        m_logInstance->IncSeverity();         
    }
};

class DecSeverity : public BaseConsole
{
public:
    virtual void Action(int)
    {
        Logger* m_logInstance = Logger::InstaceLogger();
        m_logInstance->DecSeverity();         
    }
};
 
}//ilrd

#endif