#include <iostream>

class Base
{
public:
    Base (int a_ = 8) : m_a(a_) { std::cout<<"B::Ctor"<<std::endl; }
    virtual ~Base(){std::cout<<"B::Dtor"<<std::endl;}

    virtual void Print1() const{ std::cout<<"B::Print1 B::m_a - "<< m_a << std::endl; }
    virtual void Print2() const{ std::cout<<"B::Print2" << std::endl;}
    virtual void Print3() const{ std::cout<<"B::Print3" << std::endl;}

private:
    int m_a;
};

class Derived: public Base
{
public:
    Derived() : m_b(0), p(new char)
    {
        std::cout<<"X::Ctor"<<std::endl;
    }
    ~Derived() {std::cout<<"X::Dtor"<<std::endl;}
    void Print1() const
    { 
        std::cout << "X::Print` X::m_b - " << m_b << std::endl;
        Base::Print1();
        std::cout<<"X::Print1 end"<<std::endl;
    }
    void Print2()const
    {
        std::cout << "X::Print2" << std::endl;
    }
    void Print4()const
    {
        std::cout << "X::Print4" << std::endl;
    }

private:
    int m_b;
    char *p;
};

int main()
{
    Base *b1= new Base;
    Base* b2 = new Derived;
    
    std::cout << std::endl << "main b1:" << std::endl;
    b1->Print1();
    b1->Print2();
    b1->Print3();

    std::cout << std::endl << "main b2:" << std::endl;
    b2->Print1();
    b2->Print2();
    b2->Print3();

    Derived *d = static_cast<Derived*>(b2);
    std::cout << std::endl << "main d:"<< std::endl;
    d->Print2();
    b2->Print2();
    b2->Print3();

    delete b1;
    delete b2; 
 
    return (0);
}
