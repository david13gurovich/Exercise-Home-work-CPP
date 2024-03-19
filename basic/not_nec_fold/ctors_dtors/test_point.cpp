#include <cstdlib>
#include <iostream>

#include "point.h"

int main(int argc, char const *argv[])
{    
    if (argc < 2)
    {
        std::cout << "add parameter" << '\n';
        return 1;
    }

    int max_num = atoi(argv[1]) - 1;

    Point a(3, 5, max_num);
    Point b(1, 1, max_num);
    Point c(10, 11, max_num);
    Point d;
    
    std::cout << "\nTotal Length = " << TotalLen() << "\n";

    Point e = Add(a, b);

    return (0);
}