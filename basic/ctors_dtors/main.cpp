
#include <iostream>

#include "ctor_dtor.hpp"

int main()
{
   /*  X x1;
    X x2(7, 1);
    X x3(9, 10);
    X x4(x1);

    x1 = x3;

    Y y1;
    y1.m_x.m_a = 250;
    // y1.m_x.m_b = 750 
    Y y2(y1);
    Y y3;
    y3 = y1; */
    /* ************************************************************* */

    float *f = new float(12.6);
    std::cout << *f << '\n';

    delete f;

    f = new float[15];
    std::cout << sizeof(*f) << '\n';
    
    for(size_t i = 0; i < 15; i++)
    {
        f[i] = i+0.25;
    }
    
    delete[] f;

    Counter *c1 = new Counter;

    std::cout << sizeof(*c1) << '\n';
    X *x1 = new X;
    std::cout << sizeof(*x1) << '\n';
    Y *y1= new Y;
    std::cout << sizeof(*y1) << '\n';

    delete c1;
    delete x1;
    delete y1;
    X *xp = new X[10];
    delete[] xp;


    return(0);
}