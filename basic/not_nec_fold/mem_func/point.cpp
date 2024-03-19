#include <iostream>
#include <math.h>      /* sqrt */
#include <cstdlib>

#include "point.h"

using namespace std;

void Point::AdjustBy(Point a)
{
    x += a.x;
    x %= max_limit;
    y += a.y;
    y %= max_limit;
}
 
size_t Point::Len()
{
    cout << sqrt(x * x + y * y);
    return (sqrt(x * x + y * y)); 
} 

void Point::Print(char open, char close)
{
    cout << open << x << "," << y << close << endl;
}

Point Add(Point a, Point b)
{
    Point ret = {};
    a.AdjustBy(b);
    ret.x = a.x % a.max_limit;
    ret.y = a.y % a.max_limit;

    return (ret);
}

