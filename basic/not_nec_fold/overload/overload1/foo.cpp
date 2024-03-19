#include <iostream>
#include "foo.hpp"

void Foo(int x)
{
    std::cout << x; 
    std::cout << "FOO"; 
}

/* void Foo(int i)
{
    cout << "FOO with int i: " << i << endl;
}

void Foo(char c)
{
    cout << "FOO with char c: " << c << endl;
}
 */

int main()
{
    long x = 3;
    Foo(x);

    return 0;
}