#include <iostream>
#include <math.h> /* sqrt */
#include <cstdlib>

#include "point.h"

void Point::AdjustBy(Point a)
{
    x += a.x;
    x %= max_limit;
    y += a.y;
    y %= max_limit; 
}

void Point::AdjustBy(int d_x, int d_y)
{
    x += d_x;
    x %= max_limit;
    y += d_y;
    y %= max_limit;
}
 
size_t Point::Len()
{
    std::cout << sqrt(x * x + y * y);
    return (sqrt(x * x + y * y)); 
} 

void Point::Print(char open, char close)
{
    std::cout << open << x << "," << y << close << '\n';
}

void Point::Print()
{
    char open = 0;
    char close = 0;

    switch (pare) {
    case ROUND: 
                {   open = '(';
                    close = ')';
                    break;
                }
    case SQUARE: 
                {   open = '[';
                    close = ']';
                    break;
                }
    case CURLY: 
                {   open = '{';
                    close = '}';
                    break;
                } 
    default:    
                {
                    open = '<';
                    close = '>';
                }
             break;
}
    std::cout << open << x << "," << y << close << '\n';
}

Point Add(Point a, Point b)
{
    Point ret = {};
    a.AdjustBy(b);
    ret.x = a.x % a.max_limit;
    ret.y = a.y % a.max_limit;

    return (ret);
}

void Point::InitPoint(int p_x, int p_y, int limit, ParenthesesType par)
{
    x = p_x;
    y = p_y;
    max_limit = limit;
    pare = par;
}



