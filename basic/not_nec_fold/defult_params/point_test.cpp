#include <cstdlib>
#include <iostream>

#include "point.h"

int main(int argc, char const *argv[])
{    
    Point a = {}, b = {}, c = {}, d = {}, e = {}, f = {};
    if (argc < 2)
    {
        std::cout << "add parameter" << '\n';
        return 1;
    }

    int max_num = atoi(argv[1]) - 1;

    a.InitPoint(3, 5, max_num);
    b.InitPoint(1, 1, max_num);
    c.InitPoint(10, 11, max_num);
        
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
    a.Print(Point::SQUARE);
    std::cout << "'b': " << '\n';   
    b.AdjustBy(1, 1);
    b.Print(Point::CURLY);
    std::cout << "'c': " << '\n';   
    c.AdjustBy(1, 1);
    c.Print(Point::ANGULAR);

    d.InitPoint(0, 0, max_num);
    e.InitPoint(1, 1, max_num);
    f.InitPoint(2, 2, max_num);
    d.AdjustBy(e).AdjustBy(f).AdjustBy(3, 3);
    d.Print('(', ')');

    a.Free();
    b.Free();
    c.Free();
    d.Free();
    e.Free();
    f.Free();

    Point g = {};
    g.InitPoint(3, 3, max_num);
    std::cout << *g.point_len << '\n';
    g.x = 1;
    g.y = 1;
    g.Len();
    std::cout << *g.point_len << '\n';

    g.Free();

    return (0);
}