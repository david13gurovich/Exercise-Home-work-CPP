#ifndef ILRD_RD61_COMMON_TYPES_HPP
#define ILRD_RD61_COMMON_TYPES_HPP

#include <string.h>

enum Condition {READ, WRITE, EXCEPTION, NUM_ELEMENTS}; 
typedef void (*Func)(int fd); 

namespace details 
{
int const WORD_SIZE = 1024;
int const DATA_BYTES = 4096;
int const MSG_TOTAL_BYTES = 4113;
int const BLOCK_INDEX_BYTES = 8;
int const UID_BYTES = 8;
int const PORT = 8080;
int const MAXLINE = 8000;
int const UID_OFFSET = 1;
int const BLOCK_INDEX_OFSSET = 9;
int const DATA_OFFSET = 17;
int const CLOCK_BYTES = 100;
int const PACKET_READ_SIZE_TO_SEND = 4196;
int const PACKET_READ_SIZE_RCV = 17;
int const PACKET_WRITE_SIZE_TO_SEND = 10;
int const PACKET_WRITE_SIZE_RCV = 4113;
}//detail

namespace ilrd
{
class Packet
{
public:
    Packet(int type, char *uid)
    : m_Type(type)
    {
        memcpy(m_uid, uid, details::UID_BYTES);
    }

    virtual ~Packet(){}
    
    char m_Type;
    char m_uid[details::UID_BYTES];
};
}//ilrd
#endif