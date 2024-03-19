#include <iostream>
#include <math.h> /* sqrt */
#include <cstdlib>

#include "point.h"

static size_t g_total_len = 0;

Point &Point::AdjustBy(const Point& a)
{
    x += a.x;
    y += a.y;
    AdjustToLimit();
    g_total_len =- point_len;
    Len();
    init_x = x;
    init_y = y;

    return (*this);
}

bool Point::IsEqual(Point a) const
{
    return (x == a.x && y == a.y);
}

Point &Point::AdjustBy(int d_x, int d_y)
{
    x += d_x;
    y += d_y;
    AdjustToLimit();
    g_total_len =- point_len;
    Len();
    init_x = x;
    init_y = y;

    return (*this);
}

bool Point::IsEqual() const
{
    return (x == *x_calc && y == *y_calc);
}
 
long Point::Len() const
{
    if (!IsEqual())
    {
        *x_calc = x;
        *y_calc = y;
        *point_len_ptr = sqrt(x * x + y * y);
        g_total_len += *point_len_ptr;
    }
    
    return (*point_len_ptr); 
} 

void Point::Print(const char open, const char close) const
{
    std::cout << open << x << "," << y << close << '\n';
}

void Point::Print(ParenthesesType pare) const
{
    char open = 0;
    char close = 0;

    switch (pare) 
    {
        case ROUND: 
        {   
            open = '(';
            close = ')';
            break;
        }
        case SQUARE: 
        {   
            open = '[';
            close = ']';
            break;
        }
        case CURLY: 
        {   
            open = '{';
            close = '}';
            break;
        }
        case ANGULAR:
        {
            open = '<';
            close = '>';
            break;
        }
        default:   
            break;
    }
    std::cout << open << x << "," << y << close << '\n';
}

Point Add(Point a, Point b)
{
    Point ret;
    a.AdjustBy(b);
    ret.x = a.x % a.max_limit;
    ret.y = a.y % a.max_limit;

    return (ret);
}

void Point::AdjustToLimit()
{
    x %= max_limit;
    y %= max_limit;
}

Point::Point()
    : x(2), y(2), init_x(2), init_y(2), x_calc(&init_x), y_calc(&init_y), 
    point_len(2), point_len_ptr(&point_len), max_limit(100)
{
    ;
}

Point::Point(int p_x, int p_y, int limit)
    : x(p_x), y(p_y), init_x(p_x), init_y(p_y), x_calc(&init_x), y_calc(&init_y)
    ,point_len(sqrt(x * x + y * y)), point_len_ptr(&point_len), max_limit(limit)
{
    g_total_len += *point_len_ptr;
}

Point::~Point()
{
    std::cout << "Dtor" << "\n";
    Print(Point::ROUND);
}

size_t TotalLen()
{
    return (g_total_len);
} 

Point& Point::operator=(const Point& other)
{
    x = other.x;
    y = other.y;
    x_calc = other.x_calc;
    y_calc = other.y_calc;
    point_len = other.point_len;
    point_len_ptr = other.point_len_ptr;
    max_limit = other.max_limit;

    return (*this);
}



