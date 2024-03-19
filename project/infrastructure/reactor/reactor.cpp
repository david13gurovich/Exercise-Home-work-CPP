#include <sys/time.h> //FD_SET, FD_ZERO
#include <sys/types.h> //FD_SET, FD_ZERO
#include <unistd.h> //FD_SET, FD_ZERO
#include <vector> //vector
#include <algorithm> //foreach

#include "reactor.hpp"
#include "logger_inc.hpp"
#include "wrapper_handler_excepation.hpp"
#include "wrapper_handler_read.hpp"
#include "wrapper_handler_write.hpp"
#include "cfunc_call_back.hpp"

namespace ilrd 
{

Reactor::Reactor(Logger::Severity severity, std::ostream* typeDest)
: m_log(Logger::InstaceLogger(severity, typeDest))
{}

int Reactor::GetHighestFd() const
{
    return (m_registerFds.GetHighestFd());
}

void Reactor::Register(int fd,Func ptrFunc, const Condition type)
{
    CallBackBase *funcToOperate = new CFuncCallBack(ptrFunc);
    m_registerFds.Register(fd, funcToOperate, type);
    std::cout << "Reactor::Register " << "fd is " << fd << std::endl;
}

CallBackBase *Reactor::CreateWrapperHandlerRead(Handler *handlerFunc) 
{
    return (new WrapperHandlerRead(handlerFunc));
}

CallBackBase *Reactor::CreateWrapperHandlerWrite(Handler *handlerFunc) 
{
    return (new WrapperHandlerWrite(handlerFunc));
}

CallBackBase *Reactor::CreateWrapperHandlerException(Handler *handlerFunc) 
{
    return (new WrapperHandlerException(handlerFunc));
}

typedef CallBackBase *(*funcAllocWarpperHandler)(Handler *handlerFunc);

void Reactor::Register(int fd, Handler *handlerFunc, const Condition type)
{
    static funcAllocWarpperHandler lutWarpperHandlers[] = 
    {
       CreateWrapperHandlerRead,  
       CreateWrapperHandlerWrite, 
       CreateWrapperHandlerException
    };

    CallBackBase *funcToOperate = lutWarpperHandlers[type](handlerFunc); 
    m_registerFds.Register(fd, funcToOperate, type);
	*m_log << Logger::INFO << "add register" << std::endl;
}

void Reactor::UnRegisterToAll(std::vector<int> arrFds, Condition type)
{
    size_t size = arrFds.size();
    
    for(size_t i = 0; i < size; ++i)
    {
        UnRegister(arrFds[i], type);
        close(arrFds[i]);
    }
}

Reactor::~Reactor()
{
    std::vector<int> arrReadFds = m_registerFds.GetFds(READ);
    UnRegisterToAll(arrReadFds, READ);
    
    std::vector<int> arrWriteFds = m_registerFds.GetFds(WRITE);
    UnRegisterToAll(arrWriteFds, WRITE);
    
    std::vector<int> arrExceptionFds = m_registerFds.GetFds(EXCEPTION);
    UnRegisterToAll(arrExceptionFds, EXCEPTION);
}

void Reactor::UnRegister(int fd, Condition type)
{
    m_registerFds.UnRegister(fd, type);
    *m_log << Logger::INFO << "unregister" << std::endl;
}

void Reactor::ExecuteFunc(int fd, Condition type)
{
    m_registerFds.ExecuteFunc(fd, type);
    //*m_log << Logger::INFO << "function execution" << std::endl;
}

class FdSet
{
public:
    FdSet(fd_set *fd)
    : m_toSet(fd) {}
    
    void operator() (int fd) { FD_SET(fd, m_toSet); }

private:
    fd_set *m_toSet;
};

class IsSet
{
public:
    IsSet(Condition type, Reactor *reactor, fd_set *fdsType)
    :   m_type(type), m_reactor(reactor), m_fdsType(fdsType) {}
    
    void operator() (int fd) 
    { 
        if(FD_ISSET(fd, m_fdsType))
        {
            m_reactor->ExecuteFunc(fd, m_type);
        }
    }

private:
    Condition m_type;
    Reactor *const m_reactor;
    fd_set *m_fdsType;
};

void Reactor::ZeroFds(fd_set *readFds, fd_set *writeFds, fd_set *exceptionFds)
{
    FD_ZERO(readFds);
    FD_ZERO(writeFds);
    FD_ZERO(exceptionFds);
}

void Reactor::SetFds(std::vector<int> arrReadFds, 
                    std::vector<int> arrWriteFds,
                    std::vector<int> arrExceptionFds,
                    fd_set *readFds, fd_set *writeFds, fd_set *exceptionFds)
{
    for_each(arrReadFds.begin(), arrReadFds.end(), FdSet(readFds));
    for_each(arrWriteFds.begin(), arrWriteFds.end(), FdSet(writeFds));
    for_each(arrExceptionFds.begin(), arrExceptionFds.end(), FdSet(exceptionFds));
}

void Reactor::ExecIfIsSet(std::vector<int> arrReadFds, 
                    std::vector<int> arrWriteFds,
                    std::vector<int> arrExceptionFds,
                    fd_set *readFds, fd_set *writeFds, fd_set *exceptionFds)
{
    for_each(arrReadFds.begin(), arrReadFds.end(), IsSet(READ, this, readFds)); 
    for_each(arrWriteFds.begin(), arrWriteFds.end(), IsSet(WRITE, this, writeFds));
    for_each(arrExceptionFds.begin(), arrExceptionFds.end(), IsSet(EXCEPTION, 
                                                        this, exceptionFds)); 
}

void Reactor::StartEventLoop()
{
    fd_set readFds, writeFds, exceptionFds;

    while(1)
    {
        ZeroFds(&readFds, &writeFds, &exceptionFds);

        std::vector<int> arrReadFds = m_registerFds.GetFds(READ);
        std::vector<int> arrWriteFds  = m_registerFds.GetFds(WRITE);
        std::vector<int> arrExceptionFds  = m_registerFds.GetFds(EXCEPTION);

        SetFds(arrReadFds, arrWriteFds, arrExceptionFds, 
                    &readFds, &writeFds, &exceptionFds);

        int highsetFd = GetHighestFd();
        if(-1 == select(highsetFd + 1, &readFds, &writeFds, &exceptionFds, NULL))
        {
            *m_log << Logger::ERROR << "select failed" << std::endl;
        }
        
        ExecIfIsSet(arrReadFds, arrWriteFds, arrExceptionFds, 
                            &readFds, &writeFds, &exceptionFds);
    }
}

}//ilrd