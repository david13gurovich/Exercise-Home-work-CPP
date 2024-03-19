#include <iostream> //cout
#include <cstring>

#include "test.hpp"
#include "string.hpp"

TestResult TestOperatorCat();
TestResult TestLenght();
TestResult TestSetAndGetIdx();
TestResult TestPrint();
TestResult TestStringConcat();

int main()
{
	RUN_TEST(TestOperatorCat);
    RUN_TEST(TestLenght);
    RUN_TEST(TestSetAndGetIdx);
    RUN_TEST(TestPrint);
    RUN_TEST(TestStringConcat);

	return 0;
}

TestResult TestOperatorCat()
{
    String str1("Hello");
    String str2(" world"); 
    str1 += str2;
    String ans("Hello world");
    
    REQUIRE(str1 == ans);

	return (TEST_PASS);
}

TestResult TestLenght()
{
    String str1("hello");
    
    REQUIRE(strlen("hello") == str1.Length());

    String str2(" world"); 
    str1 += str2;

    REQUIRE(strlen("Hello world") == str1.Length());

    return (TEST_PASS);
}

TestResult TestSetAndGetIdx()
{
    String str("Hello");

    REQUIRE('H' == str[0]);
    REQUIRE('e' == str[1]);
    REQUIRE('l' == str[2]);
    REQUIRE('l' == str[3]);
    REQUIRE('o' == str[4]);

    str[0] = 'h';
    REQUIRE('h' == str[0]);

    return (TEST_PASS);
}

TestResult TestPrint()
{
    String str("Hello");

    std::cout << "str: " << str << std::endl;

    return (TEST_PASS);
}

TestResult TestStringConcat()
{
	String str1("aaa");
	String str2("bbb");

	str1 +=str2;
	REQUIRE(6 == str1.Length());	
	REQUIRE(0 == strcmp(str1.c_str(), "aaabbb"));	
	printf("str1=%s\n", str1.c_str());
	printf("strlen=%lu\n", str1.Length());

	str1 +=str1;
    
 	REQUIRE(12 == str1.Length());	
	REQUIRE(0 == strcmp(str1.c_str(), "aaabbbaaabbb"));	

	return (TEST_PASS);
}