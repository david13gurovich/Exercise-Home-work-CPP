#include <iostream> //size_t

#include "point.h"
#include "polygon.hpp"
#include "test.h"

TestResult TestCtor();
TestResult TestCctor();
TestResult TestAdd();
TestResult TestOperator(); 

int main()
{
	RUN_TEST(TestCtor);
	RUN_TEST(TestCctor);
	RUN_TEST(TestAdd);
	RUN_TEST(TestOperator);

	return 0;
}

TestResult TestCtor() 
{
	Polygon newPolygon;
	Polygon toCmp(0);
	REQUIRE(true == newPolygon.IsEqual(toCmp));

	return (TEST_PASS);
}

TestResult TestAdd() 
{
	Polygon newPolygon;
	Point p1(2, 2, 100);
	Point p2(3, 3, 100);
	Point p3;

	newPolygon.Add(p1);
	newPolygon.Add(p2);
	newPolygon.Add(p3);

	//newPolygon.Print();

    REQUIRE(p1.IsEqual(newPolygon.m_points[0]));
	REQUIRE(p2.IsEqual(newPolygon.m_points[1]));
    REQUIRE(p3.IsEqual(newPolygon.m_points[2]));
	
	return (TEST_PASS);
}

TestResult TestCctor() 
{
	Polygon newPolygon;
	Point p1(2, 2, 100);
	Point p2(3, 3, 100);
	Point p3;

	newPolygon.Add(p1);
	newPolygon.Add(p2);
	newPolygon.Add(p3);

	Polygon toCmp(newPolygon);
	REQUIRE(true == newPolygon.IsEqual(toCmp));

	return (TEST_PASS);
}

TestResult TestOperator()
{
	Polygon newPolygon;
	Point p1(2, 2, 100);
	Point p2(3, 3, 100);
	Point p3;

	newPolygon.Add(p1);
	newPolygon.Add(p2);
	newPolygon.Add(p3);

	Polygon toCmp;
	toCmp = newPolygon;
	REQUIRE(true == newPolygon.IsEqual(toCmp));

	return (TEST_PASS);
}

