#ifndef ILRD_RD61_STRING_HPP
#define ILRD_RD61_STRING_HPP

#include <cstddef>
#include <iostream>

class String
{
public:

    String(const char *str = "");
    ~String();
    String(const String& other_) {}
    const char *c_str() const { return(m_str);};

private:
    char *m_str;
    String& operator=(const String& other_);
};

#endif
