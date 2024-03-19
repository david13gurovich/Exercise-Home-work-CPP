#ifndef ILRD_RD61_BASE_CONSOLE_HPP
#define ILRD_RD61_BASE_CONSOLE_HPP

#include <iostream>
#include "logger_inc.hpp"

namespace ilrd
{

class BaseConsole
{
public:
    //BaseConsole() = defult
    //~BaseConsole() = defult

    virtual void Action(int) = 0;
};

}//ilrd

#endif