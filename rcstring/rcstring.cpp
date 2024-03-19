#include <cstring> //strlen, memcpy, strcmp

#include "rcstring.hpp"

const size_t g_SIZE_OF_COUNTER = sizeof(size_t);

namespace ilrd
{
char* RCString::AllocAndCopy(const char *str, size_t addTolen)
{
    size_t strLenPlusOne = strlen(str) + 1;
    size_t sizeToAlloc = strLenPlusOne + g_SIZE_OF_COUNTER + addTolen;
    char *toReturn = new char[sizeToAlloc];
    
    RCString::InitCounter(toReturn);
    memcpy(toReturn + g_SIZE_OF_COUNTER, str, strLenPlusOne);

    return (toReturn);
}

void RCString::InitCounter(char *ptrsNum)
{
    (*(new(ptrsNum) size_t)) = 1;
}

void RCString::DealIfLastRef()
{
    if (0 == GetCountPtrs(this))
    {
        delete[] (m_strAndPtrsCount);
    }
}
void RCString::SetPtrsCount(int arithmetic)
{
    (*(new(m_strAndPtrsCount) size_t)) += arithmetic;
}

size_t GetCountPtrs(RCString* rcStr)
{
    return (*(new(rcStr->m_strAndPtrsCount) size_t));
}

RCString::RCString(const char *str)
: m_strAndPtrsCount(AllocAndCopy(str, 0))
{}

RCString::~RCString()
{ 
    SetPtrsCount(-1);
    DealIfLastRef();
}

RCString::RCString(const RCString& other)
:m_strAndPtrsCount(other.m_strAndPtrsCount)
{
    SetPtrsCount(+1);
}

RCString& RCString::operator=(const RCString& other)
{
    SetPtrsCount(-1);
    DealIfLastRef();
    
    m_strAndPtrsCount = other.m_strAndPtrsCount;
    SetPtrsCount(+1);

    return (*this);
}

bool operator==(const RCString &rcStr1, const RCString &rcStr2)
{
    return (0 == strcmp(rcStr1.c_str(), rcStr2.c_str()));
}

bool RCString::operator!=(const RCString &other) const
{
    return !(*this == other);
}

const char* RCString::c_str() const
{
    return (m_strAndPtrsCount + g_SIZE_OF_COUNTER);
}

size_t RCString::Length() const
{
    return (strlen(c_str()));
}

std::ostream &operator<<(std::ostream &os, const RCString &str)
{
    return (os << str.c_str());
}

RCString::RCChar RCString::operator[](size_t idx)
{
    return (RCString::RCChar(idx, this));
}

const char& RCString::operator[](size_t idx) const
{
    return (*(c_str() + idx));
}

RCString operator+(const RCString& str1, const RCString& str2)
{
   return (RCString(str1) += str2); 
}

RCString& RCString::operator+=(const RCString &other)
{
    SetPtrsCount(-1);
    char *newStr = AllocAndCopy(c_str(), other.Length());
    strcat(newStr + g_SIZE_OF_COUNTER, other.c_str());
    
    DealIfLastRef();
    m_strAndPtrsCount = newStr;

    return (*this);
}

RCString::RCChar::RCChar(char RCChar)
: m_char(RCChar), m_index(0), m_str(NULL)
{}

RCString::RCChar::RCChar(size_t index, RCString *str)
: m_char(*(str->c_str() + index)), m_index(index), m_str(str)
{}

char& RCString::RCChar::GetChar()
{
    return (*(m_str->m_strAndPtrsCount + g_SIZE_OF_COUNTER + m_index));
}

void RCString::SetChar()
{
    if (GetCountPtrs(this) > 1)
    {
        SetPtrsCount(-1);
        DealIfLastRef();
        m_strAndPtrsCount = AllocAndCopy(c_str(), 0);
    }
}

RCString::RCChar& RCString::RCChar::operator=(const RCChar& other)
{    
    m_str->SetChar();
    GetChar() = other.m_char;

    return (*this);
}

}//ilrd
