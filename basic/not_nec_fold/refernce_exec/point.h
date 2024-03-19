#ifndef __H_POINT_
#define __H_POINT_

struct Point
{
    enum ParenthesesType { ROUND, SQUARE, CURLY, ANGULAR };
    int x;
    int y;
    int max_limit;
    ParenthesesType pare;
    
    void InitPoint(int p_x, int p_y, int limit, ParenthesesType pare);
    Point &AdjustBy(int d_x, int d_y);
    Point &AdjustBy(const Point& a);
    void Print(char open, char close);
    void Print();
    size_t Len();
    
};

#endif
