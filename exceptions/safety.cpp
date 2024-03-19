#include <cstdlib>
#include <iostream>       // std::cerr
#include <exception>      // std::set_terminate
#include <cstdlib>

void bar(int *arr) throw(int) { throw 0; }
void fishi() throw(int) { throw 0; }
void dodo() throw(int) { throw 0; }

void myunexpected ();

void foo(bool goKaboomEarly)
{
	int *arr1 = new int [10];

	if (goKaboomEarly)
	{
		try
		{
			bar(arr1);
		}
		catch(int)
		{
			std::cerr << "catch1" << '\n';
			delete[] arr1;
			exit(0);
		}
	}
	
	int *arr2 = new int [100];
	try
	{
		fishi();
		bar(arr2);
		dodo();
	}
	catch(int)
	{
		std::cerr << "catch" << '\n';
		delete[] arr1;
		delete[] arr2;
		exit(0);
	}
	
	delete[] arr1;
	delete[] arr2;
}

int main()
{
	foo(false);
	
	// std::terminate();
		
	return (0);
}