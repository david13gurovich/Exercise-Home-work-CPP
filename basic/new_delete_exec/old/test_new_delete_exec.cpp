#include <iostream>
#include <limits> /* max_int */

#include "test.h"
#include "new_delete_exec.hpp"

TestResult TestNodeGetData();
TestResult TestNodeHasNext();
TestResult TestStackIsEmpty();
TestResult TestStackPush();
TestResult TestStackPop();
TestResult TestNodeGetNext();

int main()
{
	RUN_TEST(TestNodeGetData);
	RUN_TEST(TestNodeHasNext);
	RUN_TEST(TestStackIsEmpty);
	RUN_TEST(TestStackPush);
	RUN_TEST(TestStackPop);
	RUN_TEST(TestNodeGetNext);

	return (0);
}

TestResult TestNodeGetData()
{
	int default_num = std::numeric_limits<int>::max();
	int non_default_num = 3;
 	const Stack::Node d;
    const Stack::Node *n = &d;
    Stack::Node a(non_default_num, (Stack::Node *)n); 
    const Stack::Node *b = &a;

	REQUIRE(default_num == n->GetData());
	REQUIRE(non_default_num == b->GetData());
	
	return (TEST_PASS);
}

TestResult TestNodeHasNext()
{
 	const Stack::Node d;
    const Stack::Node *n = &d;
    Stack::Node a(3, (Stack::Node *)n); 
    const Stack::Node *b = &a;

	REQUIRE(false == n->HasNext());
	REQUIRE(true == b->HasNext());

	return (TEST_PASS);
}

TestResult TestNodeGetNext()
{
 	const Stack::Node d;
    const Stack::Node *n = &d;
    Stack::Node a(3, (Stack::Node *)n); 
    const Stack::Node *b = &a;

	REQUIRE(n == &b->GetNext());

	return (TEST_PASS);
}

TestResult TestStackIsEmpty()
{
	Stack s;
	REQUIRE(true == s.IsEmpty());

	return (TEST_PASS);
}

TestResult TestStackPush()
{
	int to_push[] = {1, 2, 3, 4}; 
	size_t arr_size = 4;
	Stack s;
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
	Stack s;
	
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
