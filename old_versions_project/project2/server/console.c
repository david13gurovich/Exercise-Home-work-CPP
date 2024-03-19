#include <stdio.h> //stdin, fgets,fprintf
#include <string.h> //stcmp
#include <stdlib.h> // exit

#include "console.h"

#define SIZE 5

static const int TO_EXIT = 1;
static const int TO_CONTINUE = 0;

namespace ilrd
{

boost::shared_ptr<BaseConsole> CreateIncSeverity(int i)
{
    (void)i;
    boost::shared_ptr<BaseConsole> toReturn(new IncSeverity);
    return (toReturn);
}

boost::shared_ptr<BaseConsole> CreateDecSeverity(int i)
{
    (void)i;
    boost::shared_ptr<BaseConsole> toReturn(new DecSeverity);
    return (toReturn);
}

boost::shared_ptr<BaseConsole> CreateExitFromGrog(int i)
{
    (void)i;
    boost::shared_ptr<BaseConsole> toReturn(new ExitFromProg);
    return (toReturn);
}

boost::shared_ptr<BaseConsole> CreatePong(int i)
{
    (void)i;
    boost::shared_ptr<BaseConsole> toReturn(new Pong);
    return (toReturn);
} 

Console::Console()
: m_factory(Factory<int, std::string, BaseConsole>())
{
    InitFactory();
}

void Console::InitFactory()
{
    m_factory.Teach("+", CreateIncSeverity);
    m_factory.Teach("-", CreateDecSeverity);
    m_factory.Teach("exit", CreateExitFromGrog);
    m_factory.Teach("ping", CreatePong); 
}

void Console::FuncToRegister(int nothing)
{
    (void)nothing;
    char toGet[SIZE] = {0};
    std::cin >> toGet;

    try
    {
        boost::shared_ptr<ilrd::BaseConsole> obj = m_factory.Create(toGet, 0);
        obj->Action(0);
    }
    catch(const ilrd::IdentifierError& e) 
    {
        std::cerr << e.what() << '\n';
    }
}

}//ilrd