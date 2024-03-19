#include <stdio.h> //stdin, fgets,fprintf
#include <string.h> //stcmp
#include <stdlib.h> // exit

#include "console.hpp"
#include "logger_configuration.hpp"
#include "call_back_base_dispatcher.hpp"

#define SIZE 5

static const int TO_EXIT = 1;
static const int TO_CONTINUE = 0;

/* namespace detail
{
char const *pathLibDir = "./commands/";
const char *pathLogFile = "./commands/logger.cgf";
} */

namespace ilrd
{

boost::shared_ptr<BaseConsole> CreateIncSeverity(DataToFactory* i)
{
    (void)i;
    boost::shared_ptr<BaseConsole> toReturn(new IncSeverity);
    return (toReturn);
}

boost::shared_ptr<BaseConsole> CreateDecSeverity(DataToFactory* i)
{
    (void)i;
    boost::shared_ptr<BaseConsole> toReturn(new DecSeverity);
    return (toReturn);
}

boost::shared_ptr<BaseConsole> CreateExitFromGrog(DataToFactory* i)
{
    (void)i;
    boost::shared_ptr<BaseConsole> toReturn(new ExitFromProg);
    return (toReturn);
}

boost::shared_ptr<BaseConsole> CreatePong(DataToFactory* i)
{
    (void)i;
    boost::shared_ptr<BaseConsole> toReturn(new Pong);
    return (toReturn);
} 

boost::shared_ptr<BaseConsole> HandleLon(DataToFactory* i)
{
    boost::shared_ptr<BaseConsole> toReturn(new Fictive);
    
    std::cout << "L-on" << std::endl;
    CallBackBaseDispatcher *toSend = new CallBackDispatcher<LoggerConfigurator>(i->m_console->GetLoggerConfig());
    
    i->m_console->GetDirMonitor().Register("loggerCfg", toSend);
    
    return (toReturn);
} 

boost::shared_ptr<BaseConsole> HandleLoff(DataToFactory* i)
{
    boost::shared_ptr<BaseConsole> toReturn(new Fictive);
    
    std::cout << "L-off" << std::endl;
    i->m_console->GetDirMonitor().UnRegister("loggerCfg");
    
    return (toReturn);
} 

boost::shared_ptr<BaseConsole> HandleSon(DataToFactory* i)
{
    boost::shared_ptr<BaseConsole> toReturn(new Fictive);
    
    std::cout << "S-on" << std::endl;
    
    CallBackBaseDispatcher *toSend = new CallBackDispatcher<SoLoader>(i->m_console->GetSoLoader());

    i->m_console->GetDirMonitor().Register("soLoader", toSend);
    
    return (toReturn);
} 

boost::shared_ptr<BaseConsole> HandleSoff(DataToFactory* i)
{
    boost::shared_ptr<BaseConsole> toReturn(new Fictive);
    
    std::cout << "S-off" << std::endl;
    i->m_console->GetDirMonitor().UnRegister("soLoader");
    
    return (toReturn);
} 

Console::Console(   DirMonitor *dirMonitor, 
                    LoggerConfigurator* loggerConfigurator, 
                    SoLoader *soLoader)
:   m_factory(Factory<DataToFactory*, std::string, BaseConsole>()), 
    m_dirMonitor(dirMonitor),
    m_soLoader(soLoader),
    m_loggerConfigurator(loggerConfigurator)
{
   // RegObjects();
    InitFactory();
}

/* void Console::RegObjects()
{
    std::cout << "Console::RegObjects" << std::endl;
    m_dirMonitor->Register("soLoader", m_CallBackSoLoader);    
    m_dirMonitor->Register("loggerCfg", m_CallBackLoggerConfig);

    //todo: deletes in dtor
} */

void Console::InitFactory()
{
    std::cout << "Console::InitFactory" << std::endl;
    m_factory.Teach("Lon", HandleLon);
    m_factory.Teach("Loff", HandleLoff);
    m_factory.Teach("Son", HandleSon);
    m_factory.Teach("Soff", HandleSoff);
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
    DataToFactory dataToFactory(this);

    try
    {
        boost::shared_ptr<ilrd::BaseConsole> obj = m_factory.Create(toGet, &dataToFactory);
        obj->Action(0);
    }
    catch(const ilrd::IdentifierError& e) 
    {
        std::cerr << e.what() << '\n';
    }
}

}//ilrd