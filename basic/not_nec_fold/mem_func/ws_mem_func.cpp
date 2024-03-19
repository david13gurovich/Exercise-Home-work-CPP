#include <iostream>
#include <stdio.h>

void Inc();

struct Counter 
{
 //   Counter *Inc();
   Counter &Inc();
    void Inc(unsigned int delta);
    void Dec();

    int m_a;
    int m_b;
    int max_limit;
};

/* Counter *Counter::Inc()
{
    ++m_a;
    m_b += 2;

    return (*this);
}  */

Counter &Counter::Inc()
{
     ++m_a;
     m_b += 2;

     return (*this);
}

void Counter::Dec()
{
    --m_a;
    m_b /= 2;
}

void Counter::Inc(unsigned int delta)
{
    std::cout << "Inc delta" << '\n';
}

void Inc()
{
    std::cout << "Inc! not a member of the struct" << '\n';
}

int main()
{
    Counter x1;
    x1.m_a = 7;
    /* Counter x2;
    x2.m_a = 0;
    x2.m_b = 16;
    x1.Inc();
    std::cout << "x1.Inc: m_a: " << x1.m_a << '\n';
    std::cout << "x1.Inc: m_b: " << x1.m_b << '\n';
    x1.Inc();
    std::cout << "x1.Inc: m_a: " << x1.m_a << '\n';
    std::cout << "x1.Inc: m_b: " << x1.m_b << '\n';
    x2.Dec();
    std::cout << "x1.Dec: m_a: " << x2.m_a << '\n';
    std::cout << "x1.Dec: m_b: " << x2.m_b << '\n';
    Inc();
    x1.Inc(3);
     */

/*     x1.Inc()->Inc()->Inc();
    std::cout << "x1 m_a: " << x1.m_a << '\n'; */

    x1.Inc().Inc().Inc();
    std::cout << "x1 m_a: " << x1.m_a << '\n';
     
    return 0;
}


