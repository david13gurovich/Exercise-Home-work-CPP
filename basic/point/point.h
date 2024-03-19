#ifndef __H_POINT_
#define __H_POINT_

struct Point
{
    enum ParenthesesType { ROUND = 0, SQUARE = 1, CURLY = 2, ANGULAR = 3 };
    int m_x;
    int m_y;
    mutable int m_saved_x;
    mutable int m_saved_y;
    mutable double m_point_len;
    int m_max_limit;

    explicit Point();
    explicit Point(int p_x, int p_y, int limit);
    ~Point();
    Point& operator=(const Point& other);   
    
    Point &AdjustBy(const Point& a);
    Point &AdjustBy(int d_x, int d_y);
    void AdjustToLimit();
    bool IsEqual(Point a) const;
    double Len() const;
    void Print(ParenthesesType pare = ROUND) const;
    void Print(char open, char close) const;
};

double TotalLen();
Point Add(const Point a, const Point b);

#endif
