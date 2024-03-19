#ifndef __H_POINT_
#define __H_POINT_

struct Point
{
    enum ParenthesesType { ROUND, SQUARE, CURLY, ANGULAR };
    int max_limit;
    int x;
    int y;
    int *x_calc;
    int *y_calc;
    long *point_len;
    
    Point &AdjustBy(const Point& a);
    Point &AdjustBy(int d_x, int d_y);
    void Free();
    bool IsEqual(Point a) const;
    long Len() const;
    void InitPoint(int p_x, int p_y, int limit);
    void Print(ParenthesesType pare = ROUND) const;
    void Print(const char open = '(', const char close = ')') const;
};

#endif
