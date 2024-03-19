#ifndef H_CREATE_FUNC_DATA
#define H_CREATE_FUNC_DATA

#include "reactor_inc.hpp" //Reactor
#include "command.hpp" //CommandSharedPtr

namespace ilrd
{
struct CreateFuncData
{
    CreateFuncData( char *rcvMsg,
                    Reactor *reactor)
    :   m_rcvMsg(rcvMsg),
        m_reactor(reactor)
        {}
    
    char *m_rcvMsg;
    Reactor *m_reactor;
};
}//ilrd

#endif