#include <stdio.h>

enum E1 {AA, BB, CC, DD};
enum E2 {TT, YY};

int main()
{
    int i;
    enum E1 e = 2;

    e = 3;
    e = TT;
    ++e;
    i = e;
}

