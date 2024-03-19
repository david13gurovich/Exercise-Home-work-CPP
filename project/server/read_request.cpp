#include <arpa/inet.h> //struct sockaddr *
#include <fstream> //file
#include <dlfcn.h> //dlsym

#include "logger_inc.hpp"
#include "exception.hpp"
#include "read_request.hpp"

const int FAIL = -1;

namespace detail
{
static const char createFunc[] = "Create";
}

namespace ilrd
{

void ReadRequest::ReadFromFile(int blockIndex, char *dataToRead)
{    
    char nameFile[20];
    strcpy(nameFile, "block");
    sprintf(nameFile + strlen(nameFile),"%u",blockIndex);
    
    std::fstream file;
    file.open(nameFile, std::fstream::in | std::fstream::binary); 
    file.read(dataToRead, details::DATA_BYTES);
    file.close();  
}

static size_t GetBlockIndex(char *blockIndex)
{
    return be64toh(*(uint64_t*)(blockIndex));
}

ReadRequest::ReadRequest(Reactor *reactor, char *rcvMsg)
:   Command(reactor),
    m_rcvFromClient(PacketRead(rcvMsg + details::UID_OFFSET, 
                                rcvMsg + details::BLOCK_INDEX_OFSSET))
{}

void ReplayRead::SendRead(int sockfd)
{
    static const int readReplySize = 4106;
    static const int dataOffset = 10;
    char bufferToSend[readReplySize];
    bufferToSend[0] = packet.m_Type;
    
    memcpy(bufferToSend + details::UID_OFFSET, packet.m_uid, sizeof(packet.m_uid));
    memcpy(bufferToSend + dataOffset, m_data, details::DATA_BYTES);
    
    int status = sendto(sockfd, bufferToSend, readReplySize, MSG_CONFIRM,
          (const struct sockaddr *)m_cliaddr, sizeof(*m_cliaddr));

    if(-1 == status)
    {
        throw SendError();
    }
}

void ReadRequest::Action(int sockfd, struct sockaddr_in *cliaddr)
{    
    char *buffer = new char[details::DATA_BYTES];    
    //need to be deleted
    ReadRequest::ReadFromFile(GetBlockIndex(m_rcvFromClient.m_blockIndex), buffer);
    
    ReplayRead *toSend = new ReplayRead(m_rcvFromClient.m_uid, 1, buffer, cliaddr); 
    //need to be deleted
 
    //m_reactor->Register(sockfd, toSend, &ReplayRead::SendRead, WRITE);
    toSend->SendRead(sockfd); 
    
    delete toSend;
    delete[] buffer;
}

}//ilrd

ilrd::CommandSharedPtr Create(ilrd::CreateFuncData& data)
{
    std::cout << "Read Create" << std::endl;
    ilrd::CommandSharedPtr toReturn(new ilrd::ReadRequest(  data.m_reactor, 
                                                            data.m_rcvMsg));
    std::cout << "after Read Create" << std::endl;
    return toReturn;
}

