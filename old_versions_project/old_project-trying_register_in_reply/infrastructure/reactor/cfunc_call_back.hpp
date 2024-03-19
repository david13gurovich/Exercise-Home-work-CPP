#ifndef ILRD_RD61_PTR_FUNC_HPP
#define ILRD_RD61_PTR_FUNC_HPP

#include "call_back_base.hpp"
#include "common_types.hpp" //func

namespace ilrd
{

class CFuncCallBack: public CallBackBase
{
public:
    CFuncCallBack(Func action)
    : m_action(action) {}
    
    virtual ~CFuncCallBack() {}
    
    virtual void ReallyDo(int fd)
    {
        m_action(fd);
    }

private:
    Func m_action;
};
}//ilrd

#endif
