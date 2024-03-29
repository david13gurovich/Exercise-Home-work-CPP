
#include <iostream>

class Y;

class X
{
public:
	X(double d): m_a(d){}
	virtual ~X(){}
    X& operator=(const Y& other); 

private:
	double m_a;

};

class Y : public X
{
public:
	Y(double d, int i) : X(d), m_b(i){}
private:
	int m_b;
};

X& X::operator=(const Y& other)
{
	return (*this);
}


int main()
{
	Y y1(0.0, 0), y2(14.2, 5);
	Y y3(0.0, 0), y4(14.2, 5);

	X& x1 = y1;
	X& x2 = y2;

	x1 = x2;
	y3 = y4;

	return 0;
}