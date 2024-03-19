#ifndef RD61_H_COMMAND 
#define RD61_H_COMMAND

#include <boost/smart_ptr/shared_ptr.hpp> //boost::shared_ptr
#include <sys/socket.h> //sockaddr_int
#include <netinet/in.h> //sockaddr_int
#include <netinet/ip.h> //sockaddr_int

#include "reactor_inc.hpp"

namespace ilrd
{
class Command
{
public:
    Command(Reactor *reactor)
    : m_reactor(reactor) {}
    
    virtual ~Command(){}
    virtual void Action(int sockfd,struct sockaddr_in *cliaddr) = 0;
protected:
    Reactor *m_reactor;
};

typedef boost::shared_ptr<Command> CommandSharedPtr;

}//ilrd
#endif