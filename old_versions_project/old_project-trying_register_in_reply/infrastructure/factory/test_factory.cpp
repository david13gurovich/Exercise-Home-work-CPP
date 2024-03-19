#include "test.hpp"
#include "factory.hpp"

TestResult Test();

int main()
{
    RUN_TEST(Test);
    
    return 0;
}

class Base
{
public:
    virtual ~Base(){}

    virtual int Read() = 0;
    virtual int Write() = 0;
};

class DerivedRead : public Base
{
public:
    virtual int Read()
    {
        std::cout << "read" << std::endl;
        return (1);
    }
    virtual int Write()
    {
        return (0);
    }
};

class DerivedWrite : public Base
{
public:
    virtual int Write()
    {
        std::cout << "Write" << std::endl;
        return (1);
    }
    virtual int Read()
    {
        return (0);
    }
};

typedef boost::shared_ptr<Base> ProductSharedPtr;

ProductSharedPtr CreateRead(int i)
{
    (void)i;
    ProductSharedPtr toReturn(new DerivedRead);
    return (toReturn);
}

ProductSharedPtr CreateWrite(int i)
{
    (void)i;
    ProductSharedPtr toReturn(new DerivedWrite);
    return (toReturn);
}

TestResult Test()
{
    ilrd::Factory <int, int, Base> factory;
    factory.Teach(READ, CreateRead);
    factory.Teach(WRITE, CreateWrite);    

    ProductSharedPtr objRead = factory.Create(READ, 0);
    REQUIRE(objRead->Read() == 1);
    REQUIRE(objRead->Write() == 0);
    
    ProductSharedPtr objWrite = factory.Create(WRITE, 0);
    REQUIRE(objWrite->Read() == 0);
    REQUIRE(objWrite->Write() == 1);
    
    return (TEST_PASS);
}
