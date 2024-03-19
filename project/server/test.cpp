#include <iostream>

#include "dispatcher.hpp"

class test 
{ 
public:     
    void OnNotify() 
    {
        //action(m_fd) 
        std::cout << "Hello" << std::endl;
    } 
}; 

int main()
{
    using namespace ilrd;

    test test1;
    CallBackBaseDispatcher *c = new CallBackDispatcher<test>(&test1);
    c->OnNotify();

    return 0;
}