#include <iostream>

class X
{
public:
    X();
    virtual~X() { std::cout << "Dtor X" << std::endl; }
private:
    double m_a;    
};

class Y: public X
{
public:
    Y();
    ~Y() { std::cout << "Dtor Y" << std::endl; }
private:
    int m_b;
};

void Foo(X x)
{
   std::cout << "Foo" << std::endl; 
}

X::X()
:m_a(0)
{
    std::cout << "Ctor X" << std::endl;
}

Y::Y()
:m_b(0)
{
    std::cout << "Ctor Y" << std::endl;
}

int main()
{
    // X* xp = new Y[2];
    // std::cout << sizeof(X) << std::endl;
    // std::cout << sizeof(Y) << std::endl;
    // delete[] static_cast<Y*>(xp);

    Y y1;
    Foo(y1);

    return 0;
}