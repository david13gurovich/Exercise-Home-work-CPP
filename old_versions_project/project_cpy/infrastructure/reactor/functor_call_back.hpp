#ifndef ILRD_RD61_WRAPPER_FUNCTOR_HPP
#define ILRD_RD61_WRAPPER_FUNCTOR_HPP

#include "call_back_base.hpp"

namespace ilrd
{

template <typename T>
class FunctorCallBack: public CallBackBase
{
public:
    FunctorCallBack(T functor)
    : m_functor(functor) {}
    
    virtual ~FunctorCallBack() {}
    
    virtual void ReallyDo(int fd)
    {
        m_functor(fd);
    }

private:
    T m_functor;
};

}//ilrd

#endif