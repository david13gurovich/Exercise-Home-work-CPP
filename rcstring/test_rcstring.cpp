#include <iostream> //cout
#include <cstring> //strcmp

#include "test.hpp"
#include "rcstring.hpp"

TestResult TestCtor();
TestResult TestCctor();
TestResult TestOperatorAssignment();
TestResult TestCStr();
TestResult TestLen();
TestResult TestPrint();
TestResult TestOperatorParenthesis();
TestResult TestOperatorPlusAndAssign();

int main()
{
	RUN_TEST(TestCtor);
	RUN_TEST(TestCctor);
    RUN_TEST(TestOperatorAssignment);
    RUN_TEST(TestCStr);
    RUN_TEST(TestLen);
    RUN_TEST(TestPrint);
    RUN_TEST(TestOperatorParenthesis);
    RUN_TEST(TestOperatorPlusAndAssign);

	return 0;
}

using namespace ilrd;

TestResult TestCtor()
{
    RCString rcStr1;
    RCString rcStr2("hello");

    REQUIRE(true);

	return (TEST_PASS);
}

TestResult TestCctor()
{
    size_t ptrNum = 1;
    RCString rcStr1("hello");

    REQUIRE(ptrNum == GetCountPtrs(&rcStr1));
    
    RCString rcStr2(rcStr1);
    ++ptrNum;
    
    REQUIRE(ptrNum == GetCountPtrs(&rcStr1));

	return (TEST_PASS);
}

TestResult TestOperatorAssignment()
{
    RCString rcStr1("hello");
    RCString rcStr2("hi");

    REQUIRE(rcStr2 != rcStr1);
    rcStr2 = rcStr1;
    REQUIRE(rcStr1 == rcStr1);

    return (TEST_PASS);   
}

TestResult TestCStr()
{
    RCString rcStr1("hello");
    REQUIRE(0 == strcmp(rcStr1.c_str(), "hello"));
    
    return (TEST_PASS);   
}

TestResult TestLen()
{
    size_t len = strlen("hello");
    RCString rcStr1("hello");
    REQUIRE(len == rcStr1.Length());
    
    return (TEST_PASS);      
}

TestResult TestPrint()
{
    RCString rcStr1("hello");
    std::cout << rcStr1 << std::endl;
    
    return (TEST_PASS);      
}

TestResult TestOperatorParenthesis()
{
    const RCString rcStrConst("world");
    REQUIRE(rcStrConst[2] == 'r');
   // REQUIRE(rcStrConst[2] = 'k'); //should be complie error
    
    RCString rcStr1("hello");
    RCString rcStr2(rcStr1);
    RCString rcStr3(rcStr1);
    rcStr3[3];
    REQUIRE(3 == GetCountPtrs(&rcStr1));

    REQUIRE(rcStr1[3] == 'l');
    REQUIRE(rcStr2[3] == 'l');
    rcStr1[3] = 'm';
    REQUIRE(rcStr1[3] == 'm');


    return (TEST_PASS);         
}

TestResult TestOperatorPlusAndAssign()
{
    RCString rcStr1("hello");
    RCString rcStr2(" world");
    RCString rcStr3(rcStr1);
    rcStr1 += rcStr2;
    REQUIRE(0 == strcmp(rcStr1.c_str(), "hello world"));
    REQUIRE(0 == strcmp(rcStr3.c_str(), "hello"));

    return (TEST_PASS);            
}