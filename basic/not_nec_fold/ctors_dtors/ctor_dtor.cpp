#include <cstdio>

struct X
{
    explicit X();
    explicit X(int a_, int b_);
    ~X();
    X(const X& other);
    X& operator = (const X& other_);

    int m_a;
    const int m_b;
};

struct Y
{
   X m_x;
   int m_i;
};

X::X()
: m_a(3), m_b(4)
{
    printf("Default Ctor: %p, %d, %d\n", (void *)this, m_a, m_b);
    m_a = 9;
    // m_b = 11;
}

X::X(int a_, int b_)
    : m_a(a_), m_b(b_)
{
        printf("Ctor non default(int, int): %p, %d, %d\n", (void *)this, m_a, m_b);

}

X::X(const X& other_)
    : m_a(other_.m_a), m_b(other_.m_b)
{
    printf("Copy Ctor: %p, %d, %d\n", (void *)this, m_a, m_b);
}

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    // m_b = other_.m_b;

     printf("Copy assignment: %p, %d, %d\n", (void *)this, m_a, m_b);

     return *this;
}

X::~X()
{
    printf("Dtor: %p, %d, %d\n", (void *)this, m_a, m_b);
}

int main()
{
    X x1;
    X x2(7, 1);
    X x3(9, 10);
    X x4(x1);

    x1 = x3;

    Y y1;
    y1.m_x.m_a = 250;
    // y1.m_x.m_b = 750 
    Y y2(y1);
    Y y3;
    y3 = y1;

    return(0);
}