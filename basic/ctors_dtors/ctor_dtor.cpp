#include <cstdio>
#include <iostream>


#include "ctor_dtor.hpp"

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

void Dec()
{
    std::cout << "Dec" << std::endl;
}