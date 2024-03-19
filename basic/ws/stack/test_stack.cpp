#include <iostream>
#include <limits> /* max_int */

#include "test.h"
#include "stack.hpp"
#include "string.hpp"

using namespace ilrd;

TestResult TestNodeGetData();
TestResult TestNodeHasNext();
TestResult TestStackIsEmpty();
TestResult TestStackPush();
TestResult TestStackPop();
TestResult TestNodeGetNext();
TestResult TestCctor();
TestResult TestOperator();
TestResult TestStackString();

int main()
{
	RUN_TEST(TestNodeGetData);
	RUN_TEST(TestNodeHasNext);
	RUN_TEST(TestStackIsEmpty);
	RUN_TEST(TestStackPush);
	RUN_TEST(TestStackPop);
	RUN_TEST(TestNodeGetNext);
	RUN_TEST(TestCctor);
	RUN_TEST(TestOperator);
	RUN_TEST(TestStackString);

	return (0);
}

TestResult TestNodeGetData()
{
	int default_num = std::numeric_limits<int>::max();
	int non_default_num = 3;
 	const Stack<int>::Node d;
    const Stack<int>::Node *n = &d;
    Stack<int>::Node a(non_default_num, (Stack<int>::Node *)n); 
    const Stack<int>::Node *b = &a;

	//REQUIRE(default_num == n->GetData());
	REQUIRE(non_default_num == b->GetData());
	
	return (TEST_PASS);
}

TestResult TestNodeHasNext()
{
 	const Stack<double>::Node d;
    const Stack<double>::Node *n = &d;
    Stack<double>::Node a(3, (Stack<double>::Node *)n); 
    const Stack<double>::Node *b = &a;

	REQUIRE(false == n->HasNext());
	REQUIRE(true == b->HasNext());

	return (TEST_PASS);
}

TestResult TestNodeGetNext()
{
 	const Stack<float>::Node d;
    const Stack<float>::Node *n = &d;
    Stack<float>::Node a(3, (Stack<float>::Node *)n); 
    const Stack<float>::Node *b = &a;

	REQUIRE(n == &b->GetNext());

	return (TEST_PASS);
}

TestResult TestStackIsEmpty()
{
	Stack<float> s;
	REQUIRE(true == s.IsEmpty());

	return (TEST_PASS);
}

TestResult TestStackPush()
{
	int to_push[] = {1, 2, 3, 4}; 
	size_t arr_size = 4;
	Stack<int> s;
	REQUIRE(true == s.IsEmpty());
	
	s.Push(to_push[0]);
	REQUIRE(to_push[0] == s.Top());
    s.Push(to_push[1]);
	REQUIRE(to_push[1] == s.Top());
    s.Push(to_push[2]);
	REQUIRE(to_push[2] == s.Top());
    s.Push(to_push[3]);
	REQUIRE(to_push[3] == s.Top());

	REQUIRE(false == s.IsEmpty());
	REQUIRE(arr_size == s.Count());
	
	return (TEST_PASS);
}

TestResult TestStackPop()
{
	int to_push[] = {1, 2, 3, 4}; 
	size_t arr_size = 4;
	Stack<int> s;
	
	s.Push(to_push[0]);
    s.Push(to_push[1]);
    s.Push(to_push[2]);
    s.Push(to_push[3]);

	REQUIRE(false == s.IsEmpty());
	REQUIRE(arr_size == s.Count());
	REQUIRE(to_push[arr_size - 1] == s.Top());
	
	s.Pop();
	REQUIRE(to_push[arr_size - 2] == s.Top());
	REQUIRE(arr_size - 1 == s.Count());
    s.Pop();
   	REQUIRE(to_push[arr_size - 3] == s.Top());
	REQUIRE(arr_size - 2 == s.Count());
    s.Pop();
   	REQUIRE(to_push[arr_size - 4] == s.Top());
	REQUIRE(arr_size - 3 == s.Count());
    s.Pop();
	REQUIRE(true == s.IsEmpty());

	return (TEST_PASS);
}

TestResult TestCctor()
{
	double to_push[] = {1, 2, 3, 4}; 
	size_t arr_size = 4;
	Stack<double> s_src;
	
	s_src.Push(to_push[0]);
    s_src.Push(to_push[1]);
    s_src.Push(to_push[2]);
    s_src.Push(to_push[3]);

	Stack<double> s_dest(s_src);
	REQUIRE(arr_size == s_dest.Count());
	REQUIRE(to_push[arr_size - 1] == s_dest.Top());
	
	s_dest.Pop();
	REQUIRE(to_push[arr_size - 2] == s_dest.Top());
    s_dest.Pop();
   	REQUIRE(to_push[arr_size - 3] == s_dest.Top());
    s_dest.Pop();
   	REQUIRE(to_push[arr_size - 4] == s_dest.Top());
    s_dest.Pop();
	REQUIRE(true == s_dest.IsEmpty());

	return (TEST_PASS);
}

TestResult TestOperator()
{
	int to_push[] = {1, 2, 3, 4}; 
	size_t arr_size = 4;
	Stack<int> s_src;
	
	s_src.Push(to_push[0]);
    s_src.Push(to_push[1]);
    s_src.Push(to_push[2]);
    s_src.Push(to_push[3]);

	Stack<int> s_dest = s_src;
	REQUIRE(arr_size == s_dest.Count());
	REQUIRE(to_push[arr_size - 1] == s_dest.Top());
	
	s_dest.Pop();
	REQUIRE(to_push[arr_size - 2] == s_dest.Top());
    s_dest.Pop();
   	REQUIRE(to_push[arr_size - 3] == s_dest.Top());
    s_dest.Pop();
   	REQUIRE(to_push[arr_size - 4] == s_dest.Top());
    s_dest.Pop();
	REQUIRE(true == s_dest.IsEmpty());

	return (TEST_PASS);
}

TestResult TestStackString()
{
	using namespace ilrd;

	Stack<String> sString;

 	String str1("Hello");
    String str2(" world"); 	
	
	sString.Push(str1);
	sString.Push(str2);

	REQUIRE(str2 == sString.Top());
	sString.Pop();
	REQUIRE(str1 == sString.Top());
	sString.Pop();
	REQUIRE(true == sString.IsEmpty());
	
	return (TEST_PASS);
}