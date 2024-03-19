#include <cstring> //strcpy, strcmp

#include "string.hpp"


static char *AllocAndCopy(const char *str)
{
    char *to_return = new char[strlen(str) + 1];
    strcpy(to_return, str);

    return (to_return);
}

String::String(const char *str)
:m_str(AllocAndCopy(str)) 
{
    std::cout << "ctor" << std::endl;
}

/* String::String(const String& other)
:m_str(AllocAndCopy(other.m_str))
{
    std::cout << "cctor" << std::endl;
} */

String::~String()
{
    delete[] m_str;
}

int main()
{
    String s1 = "hello";

    return 0;
}