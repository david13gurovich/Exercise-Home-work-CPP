#ifndef ILRD_RD61_HANDLE_HPP
#define ILRD_RD61_HANDLE_HPP

#include <cstdio>
#include <iostream>

namespace ilrd
{

class Handler
{
public:
    virtual ~Handler(){}
    virtual void Read(int fd) 
    { 
        (void)fd;
        std::cout << "Read handler " << std::endl; 
    }
    virtual void Write(int fd) 
    {
        (void)fd;
        std::cout << "write handler " << std::endl; 
    }
    virtual void Exception(int fd) 
    { 
        (void)fd; 
        std::cout << "Exception handler " << std::endl; 
    }
};

}//ilrd

#endif