#ifndef ILRD_RD61_WRAPPER_HANDLER_WRITE_HPP
#define ILRD_RD61_WRAPPER_HANDLER_WRITE_HPP

#include "call_back_base.hpp"
#include "common_types.hpp" //func
#include "handler.hpp"

namespace ilrd
{

class WrapperHandlerWrite: public CallBackBase
{
public:
    WrapperHandlerWrite(Handler *WriteFunc)
    : m_actionWrite(WriteFunc) {}

    virtual ~WrapperHandlerWrite () {}
    
    virtual void ReallyDo(int fd)
    {
        m_actionWrite->Write(fd);
    }

private:
    Handler* m_actionWrite;
};
}//ilrd

#endif