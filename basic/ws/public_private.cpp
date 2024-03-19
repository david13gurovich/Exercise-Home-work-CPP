#include <cstdio>

class X
{
//private:
    int m_a;
public:
    explicit X(int a_);
    void Foo();
    void Foo(const X &x1);
    int Getm_a();
};

X::X(int a_) 
    : m_a(a_)
{}

void X::Foo()
{
    printf("%d\n", m_a);
}

void X::Foo(const X &x1) //
{
    printf("%d\n", x1.m_a);
}

int X::Getm_a()
{
	return (m_a);
}

int main()
{
    X x1(1);
    x1.Foo();
    printf("%d\n", x1.Getm_a());
    x1.Foo(x1);

    return 0;
}
