#include <stdio.h>

void Foo(const double& num)
{
	// (void)num;
	printf("This is const, %p, %f\n", &num, num);
}

void Bar(double& num)
{
	// (void)num;
	printf("This is without const, %p, %f\n", &num, num);
}

int main()
{
	int i = 2;
	double d = 3.14;
	double &b = reinterpret_cast<double&>(i);

	Foo(i);
	Bar((reinterpret_cast<double&>(i)));

	return (0);
}