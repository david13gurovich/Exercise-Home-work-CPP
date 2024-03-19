#include <cstdlib>
#include <iostream>

#include "point.h"

int main(int argc, char const *argv[])
{    
    Point a = {}, b = {}, c = {};
    if (argc < 2)
    {
        std::cout << "add parameter" << '\n';
        return 1;
    }

    int max_num = atoi(argv[1]) - 1;

    a.InitPoint(5, 3, max_num, Point::SQUARE);
    b.InitPoint(1, 1, max_num, Point::CURLY);
    c.InitPoint(10, 11, max_num, Point::ANGULAR);
        
    std::cout << "'a': " << '\n'; 
    a.AdjustBy(b); //a (3, 4)
    a.Len(); 
    a.Print('(', ')');

    std::cout << "'b': " << '\n';   
    b.AdjustBy(c); //b(11, 12)
    b.Len();
    b.Print('(', ')');

    std::cout << "'c': " << '\n';   
    c.AdjustBy(a); // c(13, 15)
    c.Len();
    c.Print('(', ')');

    std::cout << "'a': " << '\n';   
    b.AdjustBy(c); //b(24, 27)
    b.Len();
    b.Print('(', ')');

    std::cout << "AdjustBy(int d_x, int d_y)" << '\n';

    std::cout << "'a': " << '\n';  
    a.AdjustBy(1, 1);
    a.Print();
    std::cout << "'b': " << '\n';   
    b.AdjustBy(1, 1);
    b.Print();
    std::cout << "'c': " << '\n';   
    c.AdjustBy(1, 1);
    c.Print();

    return (0);
}