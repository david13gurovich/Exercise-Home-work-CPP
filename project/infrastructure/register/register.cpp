#include <algorithm> //find, foreach, transform

#include "register_inc.hpp"

namespace ilrd 
{

void Registrator::DeleteViaType(Condition type)
{
    std::map<int,CallBackBase*>::iterator start = 
                registrationContainer[type].begin();
    std::map<int,CallBackBase*>::iterator end = 
                registrationContainer[type].end();

    for(; start != end; ++start) 
    {
        delete (start->second);
    }
}

Registrator::~Registrator()
{
    DeleteViaType(READ);
    DeleteViaType(WRITE);
    DeleteViaType(EXCEPTION);
}

bool Registrator::DoesExist(int fd, Condition type) const
{
    return (registrationContainer[type].find(fd) != 
            registrationContainer[type].end());
}

void Registrator::ExecuteFunc(int fd, Condition type)
{
    (((registrationContainer[type].find(fd))->second)->ReallyDo(fd));         
}

int Registrator::GetHighestFd() const
{    
    int maxFdReadFd = (*(max_element(registrationContainer[READ].begin(), 
                            registrationContainer[READ].end()))).first;
    int maxFdWriteFd = (*(max_element(registrationContainer[WRITE].begin(), 
                            registrationContainer[WRITE].end()))).first;
    int maxFdExceptionFd = (*(max_element(registrationContainer[EXCEPTION].begin(), 
                        registrationContainer[EXCEPTION].end()))).first;

   int higher = maxFdReadFd > maxFdWriteFd ? maxFdReadFd : maxFdWriteFd; 
   
   return (maxFdExceptionFd > higher ? maxFdExceptionFd : higher);
}

void Registrator::UnRegister(int fd, Condition type)
{
    if (DoesExist(fd, type))
    {
        delete (registrationContainer[type].find(fd))->second; 
        registrationContainer[type].erase(fd); 
    }
    else
    {
        throw UnRegisterError();
    }
}

int Registrator::GetFdFromArr(std::pair<int,CallBackBase*> iterator)
{
    return(iterator.first);
}

std::vector<int> Registrator::GetFds(Condition type) const
{
    std::vector<int> allFds(registrationContainer[type].size());
    std::transform(registrationContainer[type].begin(), 
                    registrationContainer[type].end(),
                        allFds.begin(), GetFdFromArr);
    return (allFds);
}

}//ilrd