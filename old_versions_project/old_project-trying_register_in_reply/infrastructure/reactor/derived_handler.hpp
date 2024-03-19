#ifndef ILRD_RD61_DERIVED_HANDLER_HPP
#define ILRD_RD61_DERIVED_HANDLER_HPP

#include "handler.hpp"

namespace ilrd
{

class DerviedHandler : public Handler
{
public:
    virtual ~DerviedHandler() {}
    virtual void Read(int fd)
    {
        (void)fd;
        std::cout << "read" << std::endl;
    }
    virtual void Write(int fd)
    {
        (void)fd;
        std::cout << "write" << std::endl;
    }
    virtual void Exception(int fd)
    {
        (void)fd;
        std::cout << "read" << std::endl;
    }
};

}//ilrd

#endif