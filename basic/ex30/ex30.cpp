#include <iostream>

class X
{
    public:
    /* explicit */ X();
    explicit X(int a_);
    explicit X(int a_, int b_);
    void Foo();

    private:
    int m_a;
};

X::X() : m_a(0) {}
X::X(int a_) : m_a(a_) {}
X::X(int a_, int b_) :m_a(a_+b_) {}

void X::Foo()
{
    std::cout << m_a << std::endl;
}

void Fifi(X x_)
{
    x_.Foo();
}

int main()
{
    X x1(7);
    
    //Fifi();
    Fifi(x1);
    Fifi(X(7.2));
    Fifi((X)9.3); 
    Fifi(X(3,4));
    return 0;
}


