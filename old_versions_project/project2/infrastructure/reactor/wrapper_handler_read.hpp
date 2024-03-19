#ifndef ILRD_RD61_WRAPPER_HANDLER_READ_HPP
#define ILRD_RD61_WRAPPER_HANDLER_READ_HPP

#include "call_back_base.hpp"
#include "common_types.hpp" 
#include "handler.hpp"

namespace ilrd
{

class WrapperHandlerRead: public CallBackBase
{
public:
    WrapperHandlerRead(Handler *readFunc)
    : m_actionRead(readFunc) {}

    virtual ~WrapperHandlerRead() {}
    
    virtual void ReallyDo(int fd)
    {
        m_actionRead->Read(fd);
    }

private:
    Handler *m_actionRead;
};

}//ilrd

#endif