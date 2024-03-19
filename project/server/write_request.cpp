#include <arpa/inet.h> //struct sockaddr *
#include <fstream> //file
#include <dlfcn.h> //dlsym

#include "write_request.hpp"
#include "exception.hpp"

namespace detail
{
static const char createFunc[] = "Create";
}//detail

namespace ilrd
{

void WriteRequest::WriteToFile(int blockIndex, char *dataToWrite)
{    
    char nameFile[20];
    strcpy(nameFile, "block");
    sprintf(nameFile + strlen(nameFile),"%u",blockIndex);
    
    std::fstream file;
    file.open(nameFile, std::fstream::out | std::fstream::trunc  | std::fstream::binary); 
    file.write(dataToWrite, details::DATA_BYTES);
    file.close();  
}

WriteRequest::WriteRequest( Reactor *reactor,char *rcvMsg)
    :   Command(reactor),
        m_rcvFromClient(PacketWrite(rcvMsg + details::UID_OFFSET, 
                                    rcvMsg + details::BLOCK_INDEX_OFSSET,
                                    rcvMsg + details::DATA_OFFSET))
{}

static size_t BlockIndex(char *blockIndex)
{
    return be64toh(*(uint64_t*)(blockIndex));
}

void ReplayWrite::SendWrite(int sockfd)
{
    static const int writeReplySize = 10;
    
    char bufferToSend[writeReplySize];
    bufferToSend[0] = packet.m_Type;
    memcpy(bufferToSend + 1, packet.m_uid, sizeof(packet.m_uid));
    
    int status = sendto(sockfd, bufferToSend, writeReplySize, MSG_CONFIRM,
          (const struct sockaddr *)m_cliaddr, sizeof(*m_cliaddr));
    
    if(status == -1)
    {
        throw SendError();
    }
}

void WriteRequest::Action(int sockfd, struct sockaddr_in *cliaddr)
{
    WriteRequest::WriteToFile(BlockIndex(m_rcvFromClient.m_blockIndex), m_rcvFromClient.m_data);
    ReplayWrite *toSend = new ReplayWrite(m_rcvFromClient.m_uid, 1, cliaddr); 
    
    //need to be deleted
    this->m_reactor->Register(sockfd, toSend, &ReplayWrite::SendWrite, WRITE);
} 

}//ilrd

ilrd::CommandSharedPtr Create(ilrd::CreateFuncData &data)
{
    std::cout << "Write Create" << std::endl;
    ilrd::CommandSharedPtr toReturn(new ilrd::WriteRequest( data.m_reactor,
                                                            data.m_rcvMsg));
    std::cout << "after Write Create" << std::endl;
    return (toReturn);
}
