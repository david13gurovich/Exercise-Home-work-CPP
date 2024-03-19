#ifndef ILRD_RD61_CONSOLE_HPP
#define ILRD_RD61_CONSOLE_HPP

#include "factory.hpp"
#include "logger_inc.hpp"
#include "base_console.hpp"
#include "dervied_console.hpp"

namespace ilrd
{

class Console
{
public:
    explicit Console();
    void FuncToRegister(int);
    Factory <int, std::string, BaseConsole> m_factory;
   
private:
    void InitFactory();
};

}//ilrd

#endif

