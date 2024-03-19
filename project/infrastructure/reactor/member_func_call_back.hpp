#ifndef ILRD_RD61_MEMBER_FUNC_HPP
#define ILRD_RD61_MEMBER_FUNC_HPP

#include "call_back_base.hpp"
#include "common_types.hpp" //func

namespace ilrd
{

template <typename T>
class MemberFuncCallBack: public CallBackBase
{
public:
    MemberFuncCallBack(T *objPtr, void (T::*func)(int) )
    : m_objectPtr(objPtr), m_func(func) 
    {
        //std::cout << "MemberFuncCallBack - CTOR" << std::endl;
    } 

    virtual ~MemberFuncCallBack() {}
    
    virtual void ReallyDo(int fd)
    {
        (m_objectPtr->*m_func)(fd); 
    }

private:
    T *m_objectPtr;
    void (T::*m_func)(int);
};

}//ilrd

#endif

