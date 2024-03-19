#include <cstdio>

struct T
{
    int i;
    int k;
    int j;
    double n;
};

struct Y
{
    Y(T t);
    
    T &m_tr;
};

Y::Y(T t)
    : m_tr(t)
{}

int main()
{
/*     int i = 8;
    int k = 10;
    printf("address i is: %p\n", (void *)&i);
    int &ip = i;
    printf("address ip is: %p\n", (void *)&ip);
    ip = 9;
    printf("i is %d\n", i);
    i = 300;
    printf("ip is %d\n", ip);
    ip = k;
    printf("ip is %d\n", ip);
    printf("sizeof is %lu\n", sizeof(ip));
    printf("sizeof is %lu\n", sizeof(&ip));

   /*  int &ic = i;
    printf("address ic is: %p\n", &ic);
    ic = 5.8;
    printf("i is %d\n", i); */

    T t;
    Y tr(t);
    
    printf("sizeof is %lu\n", sizeof(tr.m_tr));
    
    return (0);
}