#include <iostream>
#include <algorithm> // std::for_each

#include "dispatcher.hpp"

namespace ilrd
{

void Dispatcher::RegisterDispatcher(std::string key, 
                                    CallBackBaseDispatcher* toMonitor)
{
    std::pair<std::map<std::string, CallBackBaseDispatcher*>::iterator,bool> retInsert;
    retInsert = dispatcherContainer.insert(std::pair<std::string, CallBackBaseDispatcher*>(key ,toMonitor));         
    if (!retInsert.second)
    {
        std::cout << "Dispatcher::Register: Already exist " << std::endl;
        //throw AddRegisterError();
    } 
}

bool Dispatcher::DoesExist(std::string key) const
{
    return (dispatcherContainer.find(key) != 
            dispatcherContainer.end());
}

void Dispatcher::UnRegisterDispatcher(std::string key)
{
    if (DoesExist(key))
    {
        dispatcherContainer.erase(key); 
    }
    else
    {
        std::cout << "Dispatcher::UnRegister: Does not exist " << std::endl;
        //throw UnRegisterError();
    }
}

void Dispatcher::Notify()
{
    std::cout << "Dispatcher::Notify" << std::endl;
    Dispatch();   
}

class DispatchFunctor
{
public:    
    void operator()(std::pair<std::string, CallBackBaseDispatcher*> mapPair)
    {
        mapPair.second->OnNotify();
    }
};

void Dispatcher::Dispatch()
{
    std::cout << "Dispatcher::Dispatch foreach " << std::endl;
    
    for_each (dispatcherContainer.begin(), dispatcherContainer.end(), DispatchFunctor());
    
    std::cout << "Dispatcher::Dispatch foreach - end" << std::endl;
}

}//ilrd