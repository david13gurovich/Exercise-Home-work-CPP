#include <iostream> //std::cout

#include "logger_inc.hpp"
#include "clock.hpp"

namespace ilrd
{

ClockRequest::ClockRequest(Reactor *reactor, char *rcvMsg)
:   Command(reactor),
    m_rcvFromClient(Packet(*rcvMsg, rcvMsg + details::UID_OFFSET))
{}

void ClockRequest::Action(int sockfd,struct sockaddr_in *cliaddr)
{
    ReplyClock *toSend = new ReplyClock(m_rcvFromClient.m_uid, 1, cliaddr); 
    //need to be deleted
 
    m_reactor->Register(sockfd, toSend, &ReplyClock::SendClock, WRITE);
}

char *ReplyClock::GetCurrentTimeString()
{
    std::time_t currentTime = std::time(0);
    char * strTime = std::asctime(std::localtime(&currentTime));
    strTime[strlen(strTime)-1] = ' '; //cancel \n

    return strTime;
}

void ReplyClock::SendClock(int sockfd)
{
    static const int ClockReplySize = details::UID_OFFSET + 
                        details::BLOCK_INDEX_OFSSET + details::CLOCK_BYTES;
    
    char bufferToSend[ClockReplySize];
    bufferToSend[0] = packet.m_Type;
    memcpy(bufferToSend + details::UID_OFFSET, packet.m_uid, sizeof(packet.m_uid));
    memcpy(bufferToSend + details::UID_OFFSET + details::BLOCK_INDEX_OFSSET, 
                                GetCurrentTimeString(), details::CLOCK_BYTES);
    
    int status = sendto(sockfd, bufferToSend, ClockReplySize, MSG_CONFIRM,
          (const struct sockaddr *)m_cliaddr, sizeof(*m_cliaddr));
    
    if(status == -1)
    {
        throw SendError();
    }
}

}//ilrd

ilrd::CommandSharedPtr Create(ilrd::CreateFuncData& data)
{  
    std::cout << "clock Create" << std::endl;  
    ilrd::CommandSharedPtr toReturn
    (new ilrd::ClockRequest(data.m_reactor, data.m_rcvMsg));
    return toReturn;
}