#include <iostream>
#include <dlfcn.h> //dlopen, dlsym, dlclose
#include "test.hpp"

int main()
{
    void *handleRead = dlopen("./libCommandRead.so",  RTLD_LAZY);
    if(NULL == handleRead)
    {
        std::cout << "handleRead: NULL" << std::endl;
    }
    else
    {
        std::cout << "viva la vida" << std::endl;
    }
    
    return 0;
}