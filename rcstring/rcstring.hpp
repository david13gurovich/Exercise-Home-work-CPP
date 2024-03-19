#ifndef ILRD_RD61_RCSTRING_HPP
#define ILRD_RD61_RCSTRING_HPP

#include <iostream> //ostream

namespace ilrd
{
class RCString
{
class RCChar;
friend size_t GetCountPtrs(RCString* rcStr); 

public:
    RCString(const char *str = ""); /* not explicit */
    RCString(const RCString& other);
    RCString& operator=(const RCString& other);
    ~RCString();
    
    RCChar operator[](size_t idx);
    RCString &operator+=(const RCString &other);    
    bool operator!=(const RCString &other) const;
    const char &operator[](size_t idx) const;
    const char *c_str() const;
    size_t Length() const;
    void SetChar();
    
private:
    static char *AllocAndCopy(const char *str, size_t addTolen);
    static void InitCounter(char *ptrsNum);
    void DealIfLastRef();
    void SetPtrsCount(int arithmeticOperation);

    class RCChar
    {
    public:
        RCChar(char RCChar);
        RCChar(size_t index, RCString *str);
        // RCChar(const RCChar& other) = default;
        //~RCChar(); = default;
        RCChar& operator=(const RCChar& other);
        operator char() const { return (m_char); }
    
    private:
        char& GetChar();
        char m_char;
        size_t m_index;
        RCString *m_str; 
    };
    
    char *m_strAndPtrsCount;
};

bool operator==(const RCString &rcStr1, const RCString &rcStr2); 
RCString operator+(const RCString& str1, const RCString& str2); 
std::ostream &operator<<(std::ostream &os, const RCString &str);
} // ilrd

#endif
