#include <cstdlib>
#include <iostream>       // std::cerr
#include <exception>      // std::set_terminate
#include <cstdlib>

#include <iostream>
#include <typeinfo> 
#include <new> 
/************************    1     **************************/
/*void bar(int *arr)
{

}

void fishi() throw (int)
{
 	throw (2);
}

void dodo()
{

}

void foo(bool goKaboomEarly)
{
	int i = 42;
	int *arr1 = new int [10];

	if (goKaboomEarly)
	{
		bar(arr1);
	}

	int *arr2 = new int [100];

	try 
	{
		fishi();
	}

	catch (int x)
	{ 
		std::cerr << "hip hip!" << std::endl; 
		std::cout << i << std::endl;

		delete[] arr2;
		delete[] arr1;

		exit(2);
	}

	catch (char c)
	{ 
		exit(2);
	}

	bar(arr2);
	dodo();

	delete[] arr2;
	delete[] arr1;
}

int main()
{
	foo(1);

	return (0);
}*/

/************************    2     **************************/

int foo(int) { throw std::bad_alloc(); }

void bar() { throw std::bad_cast(); }

class X
{
public:
	~X();
	int m_a;
};

X::~X()
{
	// std::cerr << foo(m_a) << std::endl;
}

void fishi()
{
	X x1;

	foo(3);
	bar();
}

int main()
{
	try 
	{
		fishi();
	}

	catch (std::bad_alloc)
	{
		std::cerr<<"Out of memory! exiting.\n"; exit(2);
	}

	catch (std::bad_cast)
	{
		std::cerr<<"Out of cast! exiting.\n"; exit(0);
	}

	return (0);
}