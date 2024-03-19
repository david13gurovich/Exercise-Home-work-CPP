#ifndef ILRD_RD61_REGISTER_HPP
#define ILRD_RD61_REGISTER_HPP

#include <map> 
#include <vector>

#include "common_types.hpp"
#include "uncopyable.hpp"
#include "call_back_base.hpp"

namespace ilrd 
{
class Registrator: private Uncopyable
{
public: 
    //Registrator() = defult
    ~Registrator();
    
    void Register(int fd, CallBackBase* const action, Condition type); 
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
