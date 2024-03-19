#include <cstdio>
#include <iostream>

void Foo(int arg1, int args2 , float arg3 = 4);

int main()
{
    Foo(3);
    Foo(6,5);
    Foo(4 ,7, 8.7);
    Foo(4 , , 8.7);

    return (0);
}

void Foo(int arg1, int args2, float arg3)
{
    std::cout << "arg1 " << arg1 << ", args2 " << args2 << ", arg3 " << arg3 << "\n";
}
