#include <iostream>
#include <exception>
#include <typeinfo>

struct TrowAtDefCtor
{
    TrowAtDefCtor()
    {
        std::cerr << "TrowAtDefCtor DefCtor" << std::endl;
        throw std::bad_cast();
    }

    TrowAtDefCtor(int) { std::cerr << "TrowAtDefCtor Ctor(int)" << std::endl;}
    ~TrowAtDefCtor() {std::cerr << "TrowAtDefCtor Dtor" << std::endl;}
};

struct NoThrow
{
    NoThrow() {std::cerr << "NoThrow Ctor" << std::endl;}
    ~NoThrow() {std::cerr << "NoThrow Dtor" << std::endl;}
};

class X
{
public:
    X() : m_tdc(2) {std::cerr << "X Ctor" << std::endl;}
    ~X() {std::cerr << "X Dtor" << std::endl;}

private:
    NoThrow m_nt;
    TrowAtDefCtor m_tdc;
};

class Y
{
public:
    Y() {std::cerr << "Y Ctor" << std::endl;}
    ~Y() {std::cerr << "Y Dtor" << std::endl;}

private:
    TrowAtDefCtor m_tdc;
    NoThrow m_nt;
};

class Z
{
public:
    Z() {std::cerr << "Z Ctor" << std::endl;}
    ~Z() {std::cerr << "Z Dtor" << std::endl;}

private:
    NoThrow m_nt;
    TrowAtDefCtor m_tdc;
};

class YPtrs
{
public:
    YPtrs()
    : m_dtc(new TrowAtDefCtor), m_nt(new NoThrow)
    {std::cerr << "YPtrs Ctor" << std::endl;}
    ~YPtrs()
    {
        std::cerr << "YPtrs Dtor" << std::endl;
        delete m_nt;
        delete m_dtc;
    }
private:
    TrowAtDefCtor *m_dtc;
    NoThrow *m_nt;

};

class ZPtrs
{
public:
    ZPtrs()
    {
        std::cerr << "ZPtrs Ctor" << std::endl;
        m_nt = new NoThrow;
        try
        {
            m_dtc = new TrowAtDefCtor;
        }
        catch(std::bad_cast)
        {
            delete m_nt;
           std::cerr << "catch" << std::endl;
           throw std::exception();
        }
        
    }
    ~ZPtrs()
    {
        std::cerr << "ZPtrs Dtor" << std::endl;
        delete m_nt;
        delete m_dtc;
    }

private:
    TrowAtDefCtor *m_dtc;
    NoThrow *m_nt;

};

int main()
{
    try
    {
        // X var1;
        // Y var1;
        // Z var1;
        // YPtrs y;
        ZPtrs z;
    }

    catch(std::exception& e)
    {
        std::cerr << "exeption cout.what:" << e.what() << std::endl;
    }
    
    return 0;
}