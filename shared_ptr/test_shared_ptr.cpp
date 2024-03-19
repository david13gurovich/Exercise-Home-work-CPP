#include <cstdlib>

#include "test.hpp"
#include "shared_ptr.hpp"

TestResult TestCctor();
TestResult TestAssignmentOperator();
TestResult TestOperatorsTrueFalse();
TestResult TestOperatorsPointer();
TestResult TestPointersArray();
TestResult TestLikePointer();

int main()
{
	RUN_TEST(TestCctor);
	RUN_TEST(TestAssignmentOperator);
	RUN_TEST(TestOperatorsTrueFalse);
	RUN_TEST(TestOperatorsPointer);
	RUN_TEST(TestPointersArray);
	RUN_TEST(TestLikePointer);

	return (EXIT_SUCCESS);
}

TestResult TestCctor()
{
	int *x = new int(3);
	size_t totalPtr = 0;

	ilrd::SharedPtr<int> ptrTest1(x);
	++totalPtr;
	REQUIRE(totalPtr == ptrTest1.GetCount());	

	++totalPtr;
	ilrd::SharedPtr<int> ptrTest2(ptrTest1);
	REQUIRE(totalPtr == ptrTest1.GetCount());	
	REQUIRE(totalPtr == ptrTest2.GetCount());	

	return (TEST_PASS);
}

TestResult TestAssignmentOperator()
{
	int *x1 = new int(3);
	int *x2 = new int(10);
	size_t totalPtrX1 = 0;
	size_t totalPtrX2 = 0;
	
	ilrd::SharedPtr<int> ptrX1A(x1);
	ilrd::SharedPtr<int> ptrX1B(ptrX1A);
	totalPtrX1 += 2;
	REQUIRE(totalPtrX1 == ptrX1A.GetCount());	
	REQUIRE(totalPtrX1 == ptrX1B.GetCount());	

	ilrd::SharedPtr<int> ptrX2A(x2);
	ilrd::SharedPtr<int> ptrX2B(ptrX2A);
	totalPtrX2 += 2;
	REQUIRE(totalPtrX2 == ptrX2A.GetCount());
	REQUIRE(totalPtrX2 == ptrX2B.GetCount());

	ptrX2A = ptrX1A;
	--totalPtrX2;
	++totalPtrX1;
	
	REQUIRE(totalPtrX1 == ptrX1A.GetCount());
	REQUIRE(totalPtrX2 == ptrX2B.GetCount());

	ptrX2A = ptrX1A;
	REQUIRE(totalPtrX1 == ptrX1A.GetCount());
	REQUIRE(totalPtrX2 == ptrX2B.GetCount());

	return (TEST_PASS);
}

TestResult TestOperatorsTrueFalse()
{
	int *x1 = new int(3);
	int *x2 = new int(10);
	
	ilrd::SharedPtr<int> ptrX1A(x1);
	ilrd::SharedPtr<int> ptrX1B(ptrX1A);
	ilrd::SharedPtr<int> ptrX2(x2);
	
	REQUIRE(ptrX1A != ptrX2);
	REQUIRE(ptrX1B != ptrX2);
	ptrX2 = ptrX1A;
	REQUIRE(ptrX1A == ptrX2);
	REQUIRE(ptrX1B == ptrX2);
	
	if (ptrX1A)
	{
		REQUIRE(true);
	}

	if (!ptrX1A)
	{
		REQUIRE(false);
	}

	return (TEST_PASS);
}

// for: TestOperatorsPointer
class X
{
public:
	X(): m_a(3) {}
	int m_a;
};

TestResult TestOperatorsPointer()
{
	int *x1 = new int(3);
	X *x2 = new X();
	
	ilrd::SharedPtr<int> ptrInt(x1);
	ilrd::SharedPtr<X> ptrClass(x2);

	REQUIRE(*ptrInt == *x1);
	REQUIRE(ptrClass->m_a == 3);

	return (TEST_PASS);
}

TestResult TestPointersArray()
{
	ilrd::SharedPtr<int> *arr = new ilrd::SharedPtr<int>[10];

	delete[] arr;

	return (TEST_PASS);
}

class Base
{
public:
	Base(): m_a(0){}
	int m_a;
};

class Derived: public Base
{
public:
	Derived(): Base(), m_b(0){}
	int m_b;
};

TestResult TestLikePointer()
{
	int *x1 = new int(3);	
	ilrd::SharedPtr <int> ptrInt3(x1);
	ilrd::SharedPtr <const int> ptrInt3const(ptrInt3);

	int *x2 = new int(2);	
	ilrd::SharedPtr <int> ptrInt2(x2);
	ilrd::SharedPtr <const int> ptrInt2const;
	ptrInt2const = ptrInt2;

	Derived *x3 = new Derived;	
	ilrd::SharedPtr <Derived> ptrDerived(x3);
	ilrd::SharedPtr <Base> ptrBase(ptrDerived);

	return (TEST_PASS);
}

