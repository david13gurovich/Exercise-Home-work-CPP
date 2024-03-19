#include <iostream>
#include <math.h> /* sqrt */
#include <cstdlib>

#include "point.h"

Point &Point::AdjustBy(const Point& a)
{
    x += a.x;
    x %= max_limit;
    y += a.y;
    y %= max_limit;

    return (*this);
}

bool Point::IsEqual(Point a) const
{
    if (x == a.x && y == a.y)
    {
        return (true);
    }

    return (false);
}

Point &Point::AdjustBy(int d_x, int d_y)
{
    x += d_x;
    x %= max_limit;
    y += d_y;
    y %= max_limit;

    return (*this);
}
 
long Point::Len() const
{
    Point a = {};
    a.x = *x_calc;
    a.y = *y_calc;

    if (!Point::IsEqual(a))
    {
        *x_calc = x;
        *y_calc = y;
        *point_len = sqrt(x * x + y * y);
    }
    
    return (*point_len); 
} 

void Point::Print(const char open, const char close) const
{
    std::cout << open << x << "," << y << close << '\n';
}

void Point::Print(ParenthesesType pare) const
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

void Point::InitPoint(int p_x, int p_y, int limit)
{
    x = p_x;
    y = p_y;
    x_calc = (int *)malloc(sizeof(int));
    y_calc = (int *)malloc(sizeof(int));
    point_len = (long *)malloc(sizeof(long));
    Point::Len();
    *x_calc = p_x;
    *y_calc = p_y;
    max_limit = limit;
}

void Point::Free()
{
    free(x_calc);
    free(y_calc);
    free(point_len);
}



