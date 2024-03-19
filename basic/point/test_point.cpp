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
    
    std::cout << "\na Length = " << a.Len() << "";
    std::cout << "\nb Length = " << b.Len() << "";
    std::cout << "\nc Length = " << c.Len() << "";
    std::cout << "\nd Length = " << d.Len() << "";
    std::cout << "\nTotal Length = " << TotalLen() << "\n";

    a.AdjustBy(c);

    if(!a.IsEqual(c))
    {
        std::cout << "\na, new point = ";
        a.Print(Point::CURLY);
        std::cout << "a new Length = " << a.Len() << "";
    }
    else
    {
        std::cout << "\na and c are equals\n";
    }
    
    std::cout << "\nafter AdjustBy, new Total Length = " << TotalLen() << "\n";
    
    Point e = Add(a, b);
    
    return (0);
}