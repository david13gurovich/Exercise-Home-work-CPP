#ifndef RD61_H_CLOCK
#define RD61_H_CLOCK

#include <time.h>

#include "server.hpp" //CreateFuncData
#include "command.hpp" //CommandSharedPtr

namespace ilrd
{

class ClockRequest : public Command
{
public:
    ClockRequest(Reactor *reactor, char *rcvMsg);
    ~ClockRequest(){}

    void Action(int sockfd,struct sockaddr_in *cliaddr);
private:
    Packet m_rcvFromClient;
};

class ReplyClock 
{
public:
    ReplyClock(char *uid, char status, struct sockaddr_in* cliaddr)
    :   packet('c', uid),
        m_status(status),
        m_cliaddr(cliaddr)
    {
        memcpy(m_currentTime, GetCurrentTimeString(), details::CLOCK_BYTES);
    }

    void SendClock(int socket);
    static char *GetCurrentTimeString();
    
    Packet packet;
    char m_status;
    struct sockaddr_in* m_cliaddr;
    char m_currentTime[details::CLOCK_BYTES];
}; 

}//ilrd

extern "C"
{
    ilrd::CommandSharedPtr Create(ilrd::CreateFuncData &data);
    
    char GetKey() { return 'c'; }
}

#endif