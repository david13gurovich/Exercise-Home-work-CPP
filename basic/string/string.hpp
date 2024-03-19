#ifndef ILRD_RD61_STRING_HPP
#define ILRD_RD61_STRING_HPP

#include <cstddef>
#include <iostream>

class String
{
public:

    explicit String(const char *str = "");
    String(const String& other_);
    String& operator=(const String& other_);
    ~String();

    char &operator[](size_t idx); 
    const char &operator[](size_t idx) const; 
    bool operator==(const String &other_) const;
    bool operator!=(const String &other_) const;
    String &operator+=(const String &other_); 

    const char *c_str() const {return(m_str);};
    size_t Length() const;

private:
    char *m_str;

};

String operator+(const String& str1, const String& str2); 
std::ostream &operator<<(std::ostream &os_, const String &str_);

#endif
