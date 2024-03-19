#include <iostream>
#include <math.h>       /* sqrt */

using namespace std;

struct Point
{
    void AdjustBy(Point a);
    void Print(char open, char close);
    size_t Len();
    
    int x;
    int y;
};

void Point::AdjustBy(Point a)
{
    x += a.x;
    y += a.y;
}
 
size_t Point::Len()
{
    return (sqrt(x * x + y * y)); 
} 

void Point::Print(char open, char close)
{
    cout << open << x << "," << y << close << endl;
}

int main()
{
    Point a = {}, b = {};
    a.x = 2, a.y = 3;
    b.x = 1, b.y = 1;
    
    a.AdjustBy(b);
    cout << a.Len();
    a.Print('(', ')');

    return (0);
}