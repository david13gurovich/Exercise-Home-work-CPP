#include <iostream>
//#include "cast_ex28.hpp"

using namespace std;

void StaticCast()
{
  int j = 41;
  int v = 4;
  float m = (float)j/v; // c cast
  float d = static_cast<float>(j)/v;
  cout << "m = " << m << endl;
  cout << "d = " << d << endl;

}

void f(int* p) 
{
  cout <<"in f(), *p= "<< *p << endl;
}

void ConstCast()
{
 const int a = 10;
 const int* b = &a;

  // Function f() expects int*, not const int*
  //f(b);
  int* c = const_cast<int*>(b);
  f(const_cast<int*>(b));

  // Lvalue is const
  //  *b = 20;

  // Undefined behavior
  *c = 30;
  f(c);

  std::cout << "a: " << a << " " << &a << std::endl;
  std::cout << "c: " << *c <<  " " << c << std::endl;
  std::cout << "b: " << *b <<  " " << b << std::endl;  

  int a1 = 40;
  const int* b1 = &a1;
  int* c1 = const_cast<int*>(b1);

  // Integer a1, the object referred to by c1, has
  // not been declared const
  *c1 = 50;
  f(c1);

}



int main() 
{
    StaticCast();

    ConstCast();
}
