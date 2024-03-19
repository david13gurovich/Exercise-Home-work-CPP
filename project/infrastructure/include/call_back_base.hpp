#ifndef ILRD_RD61_DO_OPERATION_HPP
#define ILRD_RD61_DO_OPERATION_HPP

#include <iostream>

namespace ilrd
{

class CallBackBase
{
public:   
    virtual ~CallBackBase() {}
    virtual void ReallyDo(int fd) = 0;
};

}//ilrd

#endif