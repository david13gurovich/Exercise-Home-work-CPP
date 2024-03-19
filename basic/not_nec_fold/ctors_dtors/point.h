#ifndef __H_POINT_
#define __H_POINT_

struct Point
{
    enum ParenthesesType { ROUND, SQUARE, CURLY, ANGULAR };
    int x;
    int y;
    int init_x;
    int init_y;
    int *x_calc;
    int *y_calc;
    long point_len;
    long *point_len_ptr;
    int max_limit;

    explicit Point();
    explicit Point(int p_x, int p_y, int limit);
    ~Point();
    Point& operator=(const Point& other);   
    
    Point &AdjustBy(const Point& a);
    Point &AdjustBy(int d_x, int d_y);
    void AdjustToLimit();
    bool IsEqual(Point a) const;
    bool IsEqual() const;
    long Len() const;
    void Print(ParenthesesType pare = ROUND) const;
    void Print(const char open = '(', const char close = ')') const;
};

size_t TotalLen();
Point Add(Point a, Point b);

#endif
