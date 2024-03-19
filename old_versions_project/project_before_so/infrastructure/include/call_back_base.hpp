#ifndef ILRD_RD61_DO_OPERATION_HPP
#define ILRD_RD61_DO_OPERATION_HPP

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