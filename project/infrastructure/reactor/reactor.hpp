#ifndef ILRD_RD61_REACTOR_HPP
#define ILRD_RD61_REACTOR_HPP

#include "common_types.hpp"
#include "logger_inc.hpp" 
#include "register_inc.hpp" 
#include "handler.hpp" 
#include "member_func_call_back.hpp"
#include "functor_call_back.hpp"

namespace ilrd 
{

class Reactor : private Uncopyable
{
public:
    Reactor(Logger::Severity severity = Logger::DEBUG, std::ostream* 
                                            typeDest = &std::cout); 
    ~Reactor();
   
    template <typename T>
    void Register(int fd, T *obj, void (T::*ptrFunc)(int), const Condition type);
    template <typename T>
    void Register(int fd, T functor, const Condition type);
    void Register(int fd, Func ptrFunc, const Condition type);
    void Register(int fd, Handler *func, const Condition type);
   
    void UnRegister(int fd, const Condition type);
    
    void StartEventLoop(); 
    void ExecuteFunc(int fd, const Condition type);
    
private:
    int GetHighestFd() const;

    Registrator m_registerFds;
    Logger *m_log;
    static void ZeroFds(fd_set *readFds, fd_set *writeFds, fd_set *exceptionFds);     
    static void SetFds(std::vector<int> arrReadFds, 
            std::vector<int> arrWriteFds,
            std::vector<int> arrExceptionFds,
            fd_set *readFds, fd_set *writeFds, fd_set *exceptionFds);
    static CallBackBase *CreateWrapperHandlerRead(Handler *handlerFunc);
    static CallBackBase *CreateWrapperHandlerWrite(Handler *handlerFunc);
    static CallBackBase *CreateWrapperHandlerException(Handler *handlerFunc);
    void UnRegisterToAll(std::vector<int> arrFds, Condition type);
    void ExecIfIsSet(   std::vector<int> arrReadFds,  
                        std::vector<int> arrWriteFds,
                        std::vector<int> arrExceptionFds, 
                        fd_set *readFds, 
                        fd_set *writeFds, 
                        fd_set *exceptionFds);
};

template <typename T>
void Reactor::Register(int fd, T *obj, void (T::*ptrFunc)(int), 
                                        const Condition type)
{
    CallBackBase *funcToOperate = new MemberFuncCallBack<T>(obj, ptrFunc);
    m_registerFds.Register(fd, funcToOperate, type);     
}

template <typename T>
void Reactor::Register(int fd, T functor, const Condition type)
{
    std::cout << "Reactor::Register " << "fd is " << fd << std::endl;
    CallBackBase *funcToOperate = new FunctorCallBack<T>(functor);
    m_registerFds.Register(fd, funcToOperate, type);
}

}//ilrd

#endif

