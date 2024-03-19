#ifndef ILRD_RD61_REGISTER_HPP
#define ILRD_RD61_REGISTER_HPP

#include <map> 
#include <vector>

#include "common_types.hpp"
#include "uncopyable.hpp"
#include "call_back_base.hpp"
#include "exception.hpp" 

namespace ilrd 
{
class Registrator: private Uncopyable
{
public: 
    //Registrator() = defult
    ~Registrator();
    
    void Register(int fd, CallBackBase* const action, Condition type)
    {
        std::pair<std::map<int, CallBackBase*>::iterator,bool> returnInsert;
        returnInsert = registrationContainer[type].insert(std::pair<int, 
                                        CallBackBase *>(fd ,action));         
        if (!returnInsert.second)
        {
            std::cout << "Not Register " << std::endl;
            //throw AddRegisterError();
        } 
        std::cout << "Register fd is " << fd << std::endl;
    }
    
    void UnRegister(int fd, Condition type);
    bool DoesExist(int fd, Condition type) const;
    int GetHighestFd() const;
    std::vector<int> GetFds(Condition type) const;
    void ExecuteFunc(int fd, Condition type);

private:
    std::map<int, CallBackBase*> registrationContainer[NUM_ELEMENTS]; 
    
    static int GetFdFromArr(std::pair<int,CallBackBase*> iterator);
    void DeleteViaType(Condition type);
};

} //ilrd

#endif
