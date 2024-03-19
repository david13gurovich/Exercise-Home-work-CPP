#include <iostream>

class StaticCounter
{
private:
    static size_t s_cntr;
    size_t m_id;
public:
    StaticCounter();
    static size_t GetId();
};

size_t StaticCounter::s_cntr = 1000;

StaticCounter::StaticCounter()
: m_id(++s_cntr) {}

size_t StaticCounter::GetId()
{
    std::cout << s_cntr << std::endl;
    
    return s_cntr;
}

int main()
{
    StaticCounter x1, x2;
    x1.GetId();
    x2.GetId();

    static int i;
    std::cout << &i << std::endl;

    StaticCounter::GetId();
    
    return 0;
}