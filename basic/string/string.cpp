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
{}

String::String(const String& other)
:m_str(AllocAndCopy(other.m_str))
{}

size_t String::Length() const
{
    return (strlen(m_str));
}

String::~String()
{
    delete[] m_str;
}

String& String::operator=(const String& other)
{
    delete[] m_str;
    AllocAndCopy(other.m_str);

    return (*this);
}

bool String::operator==(const String &other_) const
{
    return (0 == strcmp(m_str, other_.m_str));
}

bool String::operator!=(const String &other_) const
{
    return (!(*this == other_));
}

String& String::operator+=(const String &other)
{
    char *newStr = new char[Length() + other.Length() + 1];
    strcpy(newStr, m_str);
    strcat(newStr, other.m_str);
    
    delete[] m_str;
    m_str = newStr;

    return (*this);
}

const char& String::operator[](size_t idx) const
{
    return (m_str[idx]);
}

char& String::operator[](size_t idx) 
{    
    return (m_str[idx]);
}

String operator+(const String& str1, const String& str2)
{
    return (String(str1) += str2);
}

std::ostream &operator<<(std::ostream &os_, const String &str)
{
    return (os_ << str.c_str());
}