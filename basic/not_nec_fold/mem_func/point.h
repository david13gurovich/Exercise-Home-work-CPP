#ifndef __H_POINT_
#define __H_POINT_

struct Point
{
    void AdjustBy(Point a);
    void Print(char open, char close);
    size_t Len();
    
    int x;
    int y;
    int max_limit;
};

#endif
