#ifndef ILRD_RD61_WRAPPER_HANDLER_EXECPATION_HPP
#define ILRD_RD61_WRAPPER_HANDLER_EXECPATION_HPP

#include "call_back_base.hpp"
#include "common_types.hpp" 
#include "handler.hpp"

namespace ilrd
{

class WrapperHandlerException: public CallBackBase
{
public:
    WrapperHandlerException(Handler *exceptionFunc)
    : m_actionExecpation(exceptionFunc) {}

    virtual ~WrapperHandlerException() {}
    
    virtual void ReallyDo(int fd)
    {
        m_actionExecpation->Exception(fd);
    }

private:
    Handler* m_actionExecpation;
};

}//ilrd

#endif