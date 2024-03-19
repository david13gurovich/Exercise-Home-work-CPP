#include <iostream> //cout
#include <cstring>  //strcmp

#include "test.hpp"
#include "bitset.hpp"

using namespace ilrd;

TestResult TestIsSet();
TestResult TestCCtor();
TestResult TestSetBit();
TestResult TestResetBit();
TestResult TestFlipBit();
TestResult TestSize();
TestResult TestCountSetBits();
TestResult TestIsAllSet();
TestResult TestIsAllReset();
TestResult TestFlipAll();
TestResult TestBooleanOperators();
TestResult TestBitwiseOperatorsAndAssignment();
TestResult TestBitwiseOperators();
TestResult TestAssignmentOperator();
TestResult TesttOperatorBracket();
TestResult TestProxy();
TestResult TestNonConstIterator();
TestResult TestConstIterator();

int main()
{
	RUN_TEST(TestIsSet);
	RUN_TEST(TestCCtor);
	RUN_TEST(TestSetBit);
	RUN_TEST(TestResetBit);
	RUN_TEST(TestFlipBit);
	RUN_TEST(TestSize);
	RUN_TEST(TestCountSetBits);
	RUN_TEST(TestIsAllSet);
	RUN_TEST(TestIsAllReset);
	RUN_TEST(TestFlipAll);
	RUN_TEST(TestBooleanOperators);
	RUN_TEST(TestBitwiseOperatorsAndAssignment);
	RUN_TEST(TestAssignmentOperator);
	RUN_TEST(TestBitwiseOperators);
	RUN_TEST(TesttOperatorBracket);
	RUN_TEST(TestProxy);
	RUN_TEST(TestNonConstIterator);
	RUN_TEST(TestConstIterator);

	return 0;
}

TestResult TestIsSet()
{
	int requestBits = 21;
	Bitset<21, unsigned int> bt;

	for (int i = 0; i < requestBits; ++i)
	{
		REQUIRE(!bt.IsSet(i));
	}

	return (TEST_PASS);
}

TestResult TestSetBit()
{
	size_t indexToSet = 2;
	size_t indexToSet2 = 21;
	size_t indexToSet3 = 100;
	Bitset<102, unsigned long> bt;
	bt.SetBit(indexToSet);
	bt.SetBit(indexToSet2);
	bt.SetBit(indexToSet3);

	REQUIRE(true == bt.IsSet(indexToSet));
	REQUIRE(true == bt.IsSet(indexToSet2));
	REQUIRE(true == bt.IsSet(indexToSet3));

	return (TEST_PASS);
}

TestResult TestResetBit()
{
	size_t indexToReset = 2;
	size_t indexToReset2 = 21;
	size_t indexToReset3 = 100;
	int requestBits = 102;

	Bitset<102, unsigned long> bt;

	for (int i = 0; i < requestBits; ++i)
	{
		bt.SetBit(i);
	}

	bt.ResetBit(indexToReset);
	bt.ResetBit(indexToReset2);
	bt.ResetBit(indexToReset3);

	REQUIRE(false == bt.IsSet(indexToReset));
	REQUIRE(false == bt.IsSet(indexToReset2));
	REQUIRE(false == bt.IsSet(indexToReset3));

	return (TEST_PASS);
}

TestResult TestFlipBit()
{
	size_t bitToFlip = 100;
	Bitset<102, unsigned long> bt;

	bt.FlipBit(bitToFlip);
	REQUIRE(true == bt.IsSet(bitToFlip));

	bt.FlipBit(bitToFlip);
	REQUIRE(false == bt.IsSet(bitToFlip));

	return (TEST_PASS);
}

TestResult TestSize()
{
	size_t requestBits = 21;
	Bitset<21, unsigned int> bt;

	REQUIRE(requestBits == bt.Size());

	return (TEST_PASS);
}

TestResult TestCountSetBits()
{
	size_t numSetBits = 3;
	size_t indexToSet = 2;
	size_t indexToSet2 = 21;
	size_t indexToSet3 = 100;
	Bitset<102, unsigned long> bt;
	bt.SetBit(indexToSet);
	bt.SetBit(indexToSet2);
	bt.SetBit(indexToSet3);

	REQUIRE(numSetBits == bt.CountSetBits());

	return (TEST_PASS);
}

TestResult TestIsAllSet()
{
	int requestBits = 102;
	Bitset<102, unsigned long> bt;
	bt.SetBit(100);
	bt.SetBit(3);

	REQUIRE(!bt.IsAllSet());

	for (int i = 0; i < requestBits; ++i)
	{
		bt.SetBit(i);
	}

	REQUIRE(bt.IsAllSet());

	return (TEST_PASS);
}

TestResult TestIsAllReset()
{
	Bitset<102, unsigned long> bt;

	REQUIRE(bt.IsAllReset());
	bt.SetBit(100);
	REQUIRE(!bt.IsAllReset());

	return (TEST_PASS);
}

TestResult TestFlipAll()
{
	Bitset<20, unsigned int> bt1;
	Bitset<21, unsigned int> bt2;
	Bitset<102, unsigned long> bt3;
	Bitset<16, unsigned char> bt4;

	REQUIRE(bt1.IsAllReset());
	bt1.FlipAll();
	REQUIRE(bt1.IsAllSet());

	REQUIRE(bt2.IsAllReset());
	bt2.FlipAll();
	REQUIRE(bt2.IsAllSet());

	REQUIRE(bt3.IsAllReset());
	bt3.FlipAll();
	REQUIRE(bt3.IsAllSet());
	std::cout << bt3.CountSetBits() << std::endl;

	REQUIRE(bt4.IsAllReset());
	bt4.FlipAll();
	REQUIRE(bt4.IsAllSet());

	return (TEST_PASS);
}

TestResult TestBooleanOperators()
{
	Bitset<20, unsigned int> bt1;
	Bitset<20, unsigned int> bt2;
	REQUIRE(bt1 == bt2);

	bt2.SetBit(2);
	REQUIRE(bt1 != bt2);

	return (TEST_PASS);
}

TestResult TestBitwiseOperatorsAndAssignment()
{
	Bitset<35, unsigned int> intBt1;
	Bitset<35, unsigned int> intBt2;
	intBt1.SetBit(2);
	intBt1.SetBit(31);
	intBt2 |= intBt1;
	REQUIRE(intBt1 == intBt2);

	intBt1.SetBit(33);
	intBt1 &= intBt2;
	REQUIRE(!intBt1.IsSet(33));

	intBt2.SetBit(7);
	intBt2.SetBit(15);
	REQUIRE(!intBt1.IsSet(7));
	REQUIRE(!intBt1.IsSet(15));

	intBt1 ^= intBt2;
	REQUIRE(intBt1.IsSet(7));
	REQUIRE(intBt1.IsSet(15));

	return (TEST_PASS);
}

TestResult TestBitwiseOperators()
{
	const int numBits = 35;
	const int bitToSet1 = 2;
	const int bitToSet2 = 27;
	const int bitToSet3 = 31;
	Bitset<numBits, unsigned int> intBt1;
	Bitset<numBits, unsigned int> intBt2;
	Bitset<numBits, unsigned int> intBtRes;
	intBt1.SetBit(bitToSet1);
	intBt1.SetBit(bitToSet3);
	intBt2.SetBit(bitToSet2);
	intBtRes = intBt2 | intBt1;

	REQUIRE(intBtRes.IsSet(bitToSet1));
	REQUIRE(intBtRes.IsSet(bitToSet3));
	REQUIRE(intBtRes.IsSet(bitToSet2));

	for (int i = 0; i < numBits; ++i)
	{
		intBtRes.ResetBit(i);
	}

	intBtRes = intBt2 & intBt1;
	REQUIRE(intBtRes.IsAllReset());

	intBt2.SetBit(31);
	intBtRes = intBt2 ^ intBt1;
	REQUIRE(intBtRes.IsSet(bitToSet1));
	REQUIRE(!intBtRes.IsSet(bitToSet3));
	REQUIRE(intBtRes.IsSet(bitToSet2));

	for (int i = 0; i < numBits; ++i)
	{
		intBtRes.ResetBit(i);
	}

	intBtRes = ~intBt1;
	for (int i = 0; i < numBits; ++i)
	{
		if (bitToSet1 == i || 31 == i)
		{
			REQUIRE(!intBtRes.IsSet(i));
		}
		else
		{
			REQUIRE(intBtRes.IsSet(i));
		}
	}

	return (TEST_PASS);
}

TestResult TestCCtor()
{
	Bitset<35, unsigned int> intBt1;
	intBt1.SetBit(2);
	intBt1.SetBit(31);
	Bitset<35, unsigned int> intBt2(intBt1);

	REQUIRE(intBt1 == intBt2);

	return (TEST_PASS);
}

TestResult TestAssignmentOperator()
{
	Bitset<35, unsigned int> intBt1;
	intBt1.SetBit(2);
	intBt1.SetBit(31);
	Bitset<35, unsigned int> intBt2;
	intBt1.SetBit(33);
	intBt1.SetBit(25);
	intBt1 = intBt2;

	REQUIRE(intBt1 == intBt2);

	return (TEST_PASS);
}

TestResult TesttOperatorBracket()
{
	const size_t bitToSet = 67;
	const int numBits = 102;
	Bitset<102, unsigned long> longBt;

	REQUIRE(longBt.IsAllReset());
	longBt.SetBit(bitToSet);
	const Bitset<102, unsigned long> longBt2(longBt);

	for (int i = 0; i < numBits; ++i)
	{
		if (i == bitToSet)
		{
			REQUIRE(1 == longBt2[i]);
		}
		else
		{
			REQUIRE(0 == longBt2[i]);
		}
	}

	return (TEST_PASS);
}

TestResult TestProxy()
{
	const int bitToChange = 9;
	Bitset<15, unsigned char> charBt;
	Bitset<15, unsigned char> charBt2;

	charBt[bitToChange] = 1;
	REQUIRE(charBt.IsSet(bitToChange));

	charBt2[bitToChange] = charBt[bitToChange];
	REQUIRE(charBt2.IsSet(bitToChange));

	return (TEST_PASS);
}

TestResult TestNonConstIterator()
{
	Bitset<8, unsigned char> charBt;
	charBt.SetBit(0);

	Bitset<8, unsigned char> ::NonCIterator it0 = charBt.Begin();
	Bitset<8, unsigned char> ::NonCIterator it1(charBt[0]);
	REQUIRE(it0 == it1);
	REQUIRE(*it0 == 1);
	
	charBt.SetBit(7);
	Bitset<8, unsigned char> ::NonCIterator it2 = charBt.End();
	Bitset<8, unsigned char> ::NonCIterator it3(charBt[7]);
	--it2;
	REQUIRE(it2 == it3); 
	REQUIRE(*it2 == 1);
	
	Bitset<35, unsigned int> intBt;
	intBt.SetBit(0);

	Bitset<35, unsigned int> ::NonCIterator it4 = intBt.Begin();
	Bitset<35, unsigned int> ::NonCIterator it5(intBt[0]);
	REQUIRE(it4 == it5);
	++it4;
	REQUIRE(it4 != it5);
	++it5;
	REQUIRE(it4 == it5);
	REQUIRE(*it5 == 0);
	
	intBt.SetBit(34);
	Bitset<35, unsigned int> ::NonCIterator it6 = intBt.End();
	Bitset<35, unsigned int> ::NonCIterator it7(intBt[34]);
	--it6;
	REQUIRE(it6 == it7); 
	
	return (TEST_PASS);
}

TestResult TestConstIterator()
{
	Bitset<8, unsigned char> charBt;
	charBt.SetBit(0);

	Bitset<8, unsigned char> ::NonCIterator it0 = charBt.Begin();
	Bitset<8, unsigned char> ::NonCIterator it1(charBt[0]);
	REQUIRE(it0 == it1);
	REQUIRE(*it0 == 1);
	
	charBt.SetBit(7);
	Bitset<8, unsigned char> ::NonCIterator it2 = charBt.End();
	Bitset<8, unsigned char> ::NonCIterator it3(charBt[7]);
	--it2;
	REQUIRE(it2 == it3); 
	REQUIRE(*it2 == 1);
	
	Bitset<35, unsigned int> intBt;
	intBt.SetBit(0);

	Bitset<35, unsigned int> ::NonCIterator it4 = intBt.Begin();
	Bitset<35, unsigned int> ::NonCIterator it5(intBt[0]);
	REQUIRE(it4 == it5);
	++it4;
	REQUIRE(it4 != it5);
	++it5;
	REQUIRE(it4 == it5);
	REQUIRE(*it5 == 0);
	
	intBt.SetBit(34);
	Bitset<35, unsigned int> ::NonCIterator it6 = intBt.End();
	Bitset<35, unsigned int> ::NonCIterator it7(intBt[34]);
	--it6;
	REQUIRE(it6 == it7); 
	
	return (TEST_PASS);
}