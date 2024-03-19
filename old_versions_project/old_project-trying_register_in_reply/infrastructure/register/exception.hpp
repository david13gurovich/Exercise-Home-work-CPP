#include <iostream> 
#include <exception>

namespace ilrd
{

class AddRegisterError: public std::logic_error
{
public:
    AddRegisterError()
    : logic_error(NULL){}
    
    virtual const char* what() const throw()
    {
        return "ERROR, trying to add exist fd";
    } 
};

class UnRegisterError: public std::logic_error
{
public:
    UnRegisterError()
    : logic_error(NULL){}

    virtual const char* what() const throw()
    {
        return "ERROR, trying to delete non exist fd";
    } 
};

class IdentifierError: public std::logic_error
{
public:
    IdentifierError()
    : logic_error(NULL){}

    virtual const char* what() const throw()
    {
        return "ERROR, identifier does not exist";
    } 
};

class TeachError: public std::logic_error
{
public:
    TeachError()
    : logic_error(NULL){}

    virtual const char* what() const throw()
    {
        return "ERROR, identifier already exist";
    } 
};

class SendError: public std::logic_error
{
public:
    SendError()
    : logic_error(NULL){}

    virtual const char* what() const throw()
    {
        return "ERROR, send to failed";
    } 
};

class RecvError: public std::logic_error
{
public:
    RecvError()
    : logic_error(NULL){}

    virtual const char* what() const throw()
    {
        return "ERROR, receive failed";
    } 
};

}//ilrd