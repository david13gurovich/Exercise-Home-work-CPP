#include <iostream>

class X
{
public:
    void FOO();
    
    class Y
    {
    public:
        void bla();
        int b;
    };

private:
    int a;
};

void X::FOO()
{
      
}

void X::Y::bla()
{
    X x;
    x.FOO();
    std::cout << X::Y::b << std::endl;
}

