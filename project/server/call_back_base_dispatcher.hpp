#ifndef ILRD_RD61_CALL_BACK_BASE_HPP
#define ILRD_RD61_CALL_BACK_BASE_HPP

namespace ilrd
{

class CallBackBaseDispatcher
{
public:
    //explicit CallBackBaseDispatcher() = default
    //virtual ~CallBackBaseDispatcher()= default

    virtual void OnNotify() = 0;
};

template <typename OBJ>
class CallBackDispatcher : public CallBackBaseDispatcher
{
public:
    explicit CallBackDispatcher(OBJ *obj)
    : m_obj(obj){}

    virtual ~CallBackDispatcher(){}

    virtual void OnNotify()
    {
        m_obj->OnNotify();
    };
private:
    OBJ *m_obj;

    void InitObjects();
};

}//ilrd

#endif