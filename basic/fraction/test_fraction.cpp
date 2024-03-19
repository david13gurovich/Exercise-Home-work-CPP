#include <iostream> //cout

#include "fraction.hpp"
#include "test.hpp"

using namespace irld;

TestResult TestCtor();
TestResult TestSetters();
TestResult TestInc();
TestResult TestDec();
TestResult TestAddToSelfOtherFraction();
TestResult TestSubtractFromSelfOtherFraction();
TestResult TestAddToSelfInt();
TestResult TestSubtractFromSelfInt();
TestResult TestMulitplyByOtherFraction();
TestResult TestIsEqualFraction();
TestResult TestIsEqualInt();
TestResult TestOperatorPlusAndMinus();
TestResult TestUnary();
TestResult TestOperatorsAndUnary();
TestResult TestOperatorOstream();
TestResult TestImplicitConvertion();
TestResult TestCastOperator();
TestResult TestOperatorPlus();
TestResult TestOperatorMinus();

int main()
{
    using namespace irld;

	RUN_TEST(TestCtor);
    RUN_TEST(TestSetters);
    RUN_TEST(TestInc);
    RUN_TEST(TestDec);
    RUN_TEST(TestAddToSelfOtherFraction);
    RUN_TEST(TestSubtractFromSelfOtherFraction);
    RUN_TEST(TestAddToSelfInt);
    RUN_TEST(TestSubtractFromSelfInt);
    RUN_TEST(TestMulitplyByOtherFraction);
    RUN_TEST(TestIsEqualFraction);
    RUN_TEST(TestIsEqualInt);
    RUN_TEST(TestOperatorPlusAndMinus);
    RUN_TEST(TestUnary);
    RUN_TEST(TestOperatorsAndUnary);
    RUN_TEST(TestOperatorOstream);
    RUN_TEST(TestImplicitConvertion);
    RUN_TEST(TestCastOperator);
    RUN_TEST(TestOperatorPlus);
    RUN_TEST(TestOperatorMinus);

	return 0;
}

TestResult TestCtor()
{
    Fraction default_fraction;
    REQUIRE(1 == default_fraction.GetDenominator());
    REQUIRE(0 == default_fraction.GetNumerator());
    REQUIRE(true == default_fraction.GetIsUndefinedValue());
    default_fraction.Print();

    Fraction non_default_fraction(2, 0);
    REQUIRE(0 == non_default_fraction.GetDenominator());
    REQUIRE(2 == non_default_fraction.GetNumerator());
    REQUIRE(false == non_default_fraction.GetIsUndefinedValue());
    non_default_fraction.Print();

    Fraction default_param_fraction(2);
    REQUIRE(1 == default_param_fraction.GetDenominator());
    REQUIRE(2 == default_param_fraction.GetNumerator());
    REQUIRE(true == default_param_fraction.GetIsUndefinedValue());
    default_param_fraction.Print();
	
	return (TEST_PASS);
}

TestResult TestSetters()
{
    Fraction f;
    f.SetNumerator(5);
    REQUIRE(1 == f.GetDenominator());
    REQUIRE(5 == f.GetNumerator());

    f.SetDenominator(10);
    REQUIRE(10 == f.GetDenominator());

	return (TEST_PASS);
}

TestResult TestInc()
{
    Fraction f(2, 5);
    f.IncByOne();
    REQUIRE(5 == f.GetDenominator());
    REQUIRE(7 == f.GetNumerator());

    Fraction f1(10000, 3);
    f1.IncByOne();
    REQUIRE(3 == f1.GetDenominator());
    REQUIRE(10003 == f1.GetNumerator());

    Fraction f2(1, 1);
    f2.IncByOne();
    REQUIRE(1 == f2.GetDenominator());
    REQUIRE(2 == f2.GetNumerator());

    Fraction f3(-3, 7);
    f3.IncByOne();
    REQUIRE(7 == f3.GetDenominator());
    REQUIRE(4 == f3.GetNumerator()); 
    
    return (TEST_PASS);
}

TestResult TestDec()
{
    Fraction f(2, 5);
    f.DecByOne();
    REQUIRE(5 == f.GetDenominator());
    REQUIRE(-3 == f.GetNumerator());

    Fraction f1(10000, 3);
    f1.DecByOne();
    REQUIRE(3 == f1.GetDenominator());
    REQUIRE(9997 == f1.GetNumerator());

    Fraction f2(1, 1);
    f2.DecByOne();
    REQUIRE(1 == f2.GetDenominator());
    REQUIRE(0 == f2.GetNumerator());

    Fraction f3(-3, 7);
    f3.DecByOne();
    REQUIRE(7 == f3.GetDenominator());
    REQUIRE(-10 == f3.GetNumerator());
    
    return (TEST_PASS);
}

TestResult TestAddToSelfOtherFraction()
{
    Fraction f(2, 5);
    Fraction toAddNotValid(8, 0);
    f.AddToSelfOtherFraction(toAddNotValid);

    Fraction f2(3, 8);
    Fraction ToAdd(1, 9);
    f2.AddToSelfOtherFraction(ToAdd);
    REQUIRE(72 == f2.GetDenominator());
    REQUIRE(35 == f2.GetNumerator());
    REQUIRE(true == f2.GetIsUndefinedValue());

    Fraction f3(1, 4);
    Fraction ToAddNegative(-6, 7);
    f3.AddToSelfOtherFraction(ToAddNegative);
    REQUIRE(28 == f3.GetDenominator());
    REQUIRE(-17 == f3.GetNumerator());
    REQUIRE(true == f3.GetIsUndefinedValue());

    return (TEST_PASS);
}

TestResult TestSubtractFromSelfOtherFraction()
{
    Fraction f(2, 5);
    Fraction toSubNotValid(8, 0);
    f.SubtractFromSelfOtherFraction(toSubNotValid);

    Fraction f2(3, 8);
    Fraction ToSub(1, 9);
    f2.SubtractFromSelfOtherFraction(ToSub);
    REQUIRE(72 == f2.GetDenominator());
    REQUIRE(19 == f2.GetNumerator());
    REQUIRE(true == f2.GetIsUndefinedValue());

    Fraction f3(1, 4);
    Fraction ToSubNegative(-6, 7);
    f3.SubtractFromSelfOtherFraction(ToSubNegative);
    REQUIRE(28 == f3.GetDenominator());
    REQUIRE(31 == f3.GetNumerator());
    REQUIRE(true == f3.GetIsUndefinedValue());

    return (TEST_PASS);
}

TestResult TestAddToSelfInt()
{
    int num = 5;
    Fraction f2(3, 8);
    f2.AddToSelfInt(num);
    REQUIRE(8 == f2.GetDenominator());
    REQUIRE(43 == f2.GetNumerator());
    REQUIRE(true == f2.GetIsUndefinedValue());

    int negative_num = -6;
    Fraction f3(1, 4);
    f3.AddToSelfInt(negative_num);
    REQUIRE(4 == f3.GetDenominator());
    REQUIRE(-23 == f3.GetNumerator());
    REQUIRE(true == f3.GetIsUndefinedValue());
    
    return (TEST_PASS);
}

TestResult TestSubtractFromSelfInt()
{
    int num = 5;
    Fraction f2(3, 8);
    f2.SubtractFromSelfInt(num);
    REQUIRE(8 == f2.GetDenominator());
    REQUIRE(-37 == f2.GetNumerator());
    REQUIRE(true == f2.GetIsUndefinedValue());

    int negative_num = -6;
    Fraction f3(1, 4);
    f3.SubtractFromSelfInt(negative_num);
    REQUIRE(4 == f3.GetDenominator());
    REQUIRE(25 == f3.GetNumerator());
    REQUIRE(true == f3.GetIsUndefinedValue());

    return (TEST_PASS);
}

TestResult TestMulitplyByOtherFraction()
{
    Fraction f(2, 5);
    Fraction toSubNotValid(8, 0);
    f.MulitplyByOtherFraction(toSubNotValid);

    Fraction f2(3, 8);
    Fraction ToSub(1, 9);
    f2.MulitplyByOtherFraction(ToSub);
    REQUIRE(72 == f2.GetDenominator());
    REQUIRE(3 == f2.GetNumerator());
    REQUIRE(true == f2.GetIsUndefinedValue());

    Fraction f3(1, 4);
    Fraction ToSubNegative(-6, 7);
    f3.MulitplyByOtherFraction(ToSubNegative);
    REQUIRE(28 == f3.GetDenominator());
    REQUIRE(-6 == f3.GetNumerator());
    REQUIRE(true == f3.GetIsUndefinedValue());
    
    return (TEST_PASS);
}

TestResult TestIsEqualFraction()
{
    Fraction f(2, 5);
    Fraction equal(2, 5);
    REQUIRE(true == f.IsEqual(equal));

    Fraction f2(-3, 8);
    Fraction equalWithNegativeNumerator(-3, 8);
    REQUIRE(true == f2.IsEqual(equalWithNegativeNumerator));

    Fraction f3;
    Fraction equalDefault;
    REQUIRE(true == f3.IsEqual(equalDefault));

    Fraction notEqual(3, 5);
    REQUIRE(false == f3.IsEqual(notEqual));

    return (TEST_PASS);
}

TestResult TestIsEqualInt()
{
    Fraction f(2);
    REQUIRE(true == f.IsEqual(2));
    REQUIRE(false == f.IsEqual(3));

    Fraction f2(-3);
    REQUIRE(true == f2.IsEqual(-3));

    Fraction f3;
    REQUIRE(true == f3.IsEqual(0));

    return (TEST_PASS);
}

TestResult TestOperatorPlusAndMinus()
{
    Fraction f1(1, 3);
    Fraction f2(4, 7);

    REQUIRE(19 == (f1+f2).GetNumerator());   
    REQUIRE(21 == (f1+f2).GetDenominator());   
    REQUIRE(-5 == (f1-f2).GetNumerator());   
    REQUIRE(21 == (f1-f2).GetDenominator());   
    
    return (TEST_PASS);
}

TestResult TestUnary()
{
    Fraction f1(1, 3);
    Fraction f2;
    Fraction f3(-1, 3);
    
    REQUIRE(-1 == -f1.GetNumerator());   
    f1.Print();
    REQUIRE(0 == -f2.GetNumerator());   
    f2.Print();
    REQUIRE(1 == -f3.GetNumerator());   
    f3.Print();

    return (TEST_PASS);
}

TestResult TestOperatorsAndUnary()
{
    Fraction f1(1, 2);
    Fraction f2(3, 4);
    
    ++f1 + -(++f2);
    (f1++) - +(f2--);

    REQUIRE(2 == f1.GetDenominator());
    REQUIRE(5 == f1.GetNumerator());
    REQUIRE(4 == f2.GetDenominator());
    REQUIRE(3 == f2.GetNumerator());

    return (TEST_PASS);
}

TestResult TestOperatorOstream()
{
    Fraction f(1, 2);
    std::cout << f << std::endl;

    return (TEST_PASS);
}

TestResult TestImplicitConvertion()
{
    Foo(3);
    
    return (TEST_PASS);
}

TestResult TestCastOperator()
{
    Fraction f(1, 2);
    int castFractionInt = int(f);
    REQUIRE(0 == castFractionInt);
    
    float castFractionFloat = float(f);
    float delta = 0.001;
    REQUIRE(0.5 - castFractionFloat < delta); 

    return (TEST_PASS);   
}

TestResult TestOperatorPlus()
{
    Fraction r1(1, 2), r2(3);
    r1 + r2;
    r1 + Fraction(3);
    Fraction(3) + r1;

    return (TEST_PASS);   
}

TestResult TestOperatorMinus()
{
    Fraction r1(1, 2), r2(3);
    r1 - r2;
    r1 - Fraction(3);
    Fraction(3) - r1;

    return (TEST_PASS);   
}