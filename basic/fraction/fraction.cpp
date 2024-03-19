#include <iostream> //cout
#include <algorithm> //gcd
#include <cmath> // abs

#include "fraction.hpp"

#define UNUSED(a) ((void)(a))

namespace irld
{

Fraction::Fraction()
:   m_numerator(0), 
    m_denominator(1), 
    m_isUndefinedValue(true)
{}

Fraction::Fraction(int numerator, unsigned int denominator)
:   m_numerator(numerator),
    m_denominator(denominator), 
    m_isUndefinedValue(IsValidValue()) 
{}

Fraction::~Fraction()
{}

Fraction::Fraction(const Fraction& other)
:   m_numerator(other.m_numerator),
    m_denominator(other.m_denominator),
    m_isUndefinedValue(other.m_isUndefinedValue)
{}

Fraction& Fraction::operator=(const Fraction& other)
{
   m_numerator = other.m_numerator;
   m_denominator = other.m_denominator;
   m_isUndefinedValue = other.m_isUndefinedValue;

   return (*this); 
}

bool Fraction::IsValidValue() const
{
    return !(0 == m_denominator && 0 != m_numerator);
}

bool Fraction::GetIsUndefinedValue() const
{
    return (m_isUndefinedValue);
}

int Fraction::GetNumerator() const
{
    return (m_numerator);
}

unsigned Fraction::GetDenominator() const
{
    return (m_denominator);
}

double Fraction::GetFraction() const
{
    if (m_isUndefinedValue == false)
    {
        std::cout << "Illegal fraction" << std::endl;
        
        return (NAN);
    }

    return (m_numerator / m_denominator);
}

void Fraction::Print() const
{
    if (m_isUndefinedValue == false)
    {
        std::cout << "Illegal fraction" << std::endl;
        
        return;
    }

    std::cout << m_numerator << "/" << m_denominator << std::endl;
}

void Fraction::SetNumerator(int new_numerator)
{
    m_numerator = new_numerator;
}

void Fraction::SetDenominator(unsigned int new_denumerator)
{
    m_denominator = new_denumerator; 

    m_isUndefinedValue = IsValidValue();
}

Fraction& Fraction::Inc(int num)
{
    m_numerator += num *m_denominator;

    return (*this);
}

Fraction& Fraction::IncByOne()
{
    Inc(1);

    return (*this);
}

Fraction& Fraction::DecByOne()
{
    Inc(-1);

    return (*this);
}

Fraction &Fraction::Calc(const Fraction& other, Sign sign)
{
    if (false == other.m_isUndefinedValue)
    {
        return (*this);
    }

    m_numerator = (m_numerator * other.m_denominator) 
                + (sign * (other.m_numerator * m_denominator));
    
    UpdateDenomiator(other);

    return (*this);
}

Fraction &Fraction::UpdateDenomiator(const Fraction &other)
{
    m_denominator *= other.m_denominator;

    return (*this);
}

Fraction& Fraction::AddToSelfOtherFraction(const Fraction &other)
{
    Calc(other, PLUS);

    return (*this);
}

Fraction& Fraction::SubtractFromSelfOtherFraction(const Fraction &other)
{
    Calc(other, MINUS);

    return (*this);
}

Fraction& Fraction::MulitplyByOtherFraction(const Fraction &other)
{
    if (false == other.m_isUndefinedValue)
    {
        return (*this);
    }

    m_numerator *= other.m_numerator;
    UpdateDenomiator(other);

    return (*this);
}

Fraction& Fraction::AddToSelfInt(int toAdd)
{
    m_numerator += (toAdd * m_denominator);

    return (*this);
}

Fraction& Fraction::SubtractFromSelfInt(int toSubstract)
{
    m_numerator -= (toSubstract * m_denominator);

    return (*this);
}

bool Fraction::IsEqual(const Fraction &toCmp) const
{
    return (toCmp.m_denominator * m_numerator == 
            toCmp.m_numerator * m_denominator);
}

bool Fraction::IsEqual(const int toCmp) const
{
    Fraction fractionToCmp(toCmp);
    
    return (IsEqual(fractionToCmp));
}

Fraction& Fraction::operator--()
{
    return (DecByOne());
}

Fraction& Fraction::operator++()
{
    return (IncByOne());
}

bool Fraction::operator==(int num) const
{
    return (IsEqual(num));
}

bool Fraction::operator==(const Fraction& other) const
{
    return (IsEqual(other));
}

Fraction& Fraction::operator+=(const Fraction& other)
{
    return (AddToSelfOtherFraction(other));
}

Fraction& Fraction::operator+=(int num)
{
    return (AddToSelfInt(num));
}

Fraction& Fraction::operator-=(int num)
{
    return (SubtractFromSelfInt(num));
}

Fraction& Fraction::operator-=(const Fraction& other)
{
    return (SubtractFromSelfOtherFraction(other));
}

Fraction& Fraction::operator*=(const Fraction& other)
{
    return (MulitplyByOtherFraction(other));
}

Fraction operator+(const Fraction& f1, const Fraction& f2)
{
    return (Fraction(f1)+= f2);
}

Fraction operator-(const Fraction& f1, const Fraction& f2)
{
    return (Fraction(f1)-= f2);
}

Fraction& Fraction::operator--(int num)
{
    UNUSED(num);

    DecByOne();

    return (*this);
}

Fraction& Fraction::operator++(int num)
{
    UNUSED(num);

    IncByOne();

    return (*this);
}

std::ostream& operator<<(std::ostream& os, Fraction& f)
{
    os << f.GetNumerator() << '/'<< f.GetDenominator();

    return (os);
}

void Foo(Fraction f)
{
    f.Print(); 
}

Fraction::operator int()
{
    return (GetFraction());
}

Fraction::operator float()
{
    float numerator = static_cast <float> (GetNumerator());
    
    return (numerator / GetDenominator());
}

}