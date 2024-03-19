#ifndef ILRD_RD61_fraction_HPP
#define ILRD_RD61_fraction_HPP

#include <iostream>

namespace irld
{

class Fraction
{
public:
    Fraction();
    Fraction(int m_numerator, unsigned int m_denominator = 1);
    Fraction(const Fraction& other);
    Fraction& operator=(const Fraction& other);
    Fraction& operator--();
    Fraction& operator--(int num);
    Fraction& operator++(int num);
    Fraction& operator++();
    operator int();
    operator float();
    
    inline Fraction operator+() { return (*this); }
    inline Fraction operator-() 
    {
        Fraction tmp(*this);
        tmp.m_numerator *= (-1);

        return (tmp);
    }

    friend std::ostream& operator<<(std::ostream& os, Fraction& f); 
    bool operator==(int num) const;
    bool operator==(const Fraction& other) const;
    Fraction& operator+=(const Fraction& other);
    Fraction& operator+=(int num);
    Fraction& operator-=(int num);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    ~Fraction();
    Fraction& AddToSelfOtherFraction(const Fraction &other);
    Fraction& SubtractFromSelfOtherFraction(const Fraction &other);
    Fraction& AddToSelfInt(int toAdd);
    Fraction& SubtractFromSelfInt(int toSubstract);
    Fraction& MulitplyByOtherFraction(const Fraction &other);
    Fraction& IncByOne();
    Fraction& DecByOne();
    void Print() const;
    bool IsEqual(const Fraction &toCmp) const;
    bool IsEqual(const int toCmp) const;
    bool GetIsUndefinedValue() const;
    int GetNumerator() const;
    unsigned GetDenominator() const;
    void SetNumerator(int new_numerator);
    void SetDenominator(unsigned int new_denumerator);

private:
    int m_numerator;
    unsigned int m_denominator;
    bool m_isUndefinedValue;
    bool IsValidValue() const;
    Fraction &UpdateDenomiator(const Fraction &other);
    double GetFraction() const;
    Fraction& Inc(int num);
    enum Sign { PLUS = 1, MINUS = -1 }; 
    Fraction& Calc(const Fraction& other, Sign sign);
};

Fraction operator+(const Fraction& f1, const Fraction& f2);
Fraction operator-(const Fraction& f1, const Fraction& f2);
void Foo(Fraction f);

}

#endif
