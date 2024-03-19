#ifndef ILRD_RD61_DISPATCHER_HPP
#define ILRD_RD61_DISPATCHER_HPP

#include <map>
#include <string>

#include "call_back_base_dispatcher.hpp"

namespace ilrd
{

class Dispatcher
{
public:
    //explicit Dispatcher() = default
    //~Dispatcher() = default
    
    void RegisterDispatcher(std::string key, CallBackBaseDispatcher* toMonitor);
    void UnRegisterDispatcher(std::string key);
    void Notify();
    void Dispatch();

private:
    std::map<std::string, CallBackBaseDispatcher*>dispatcherContainer; 

    bool DoesExist(std::string key) const;
};

}//ilrd

#endif