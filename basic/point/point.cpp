#include <iostream>
#include <math.h> /* sqrt */
#include <cstdlib>

#include "point.h"

static double g_total_len = 0;

static void AdjustByConv(Point &point, int d_x, int d_y)
{
    point.m_x += d_x;
    point.m_y += d_y;
    point.AdjustToLimit();
    point.Len();
}

Point &Point::AdjustBy(const Point& a)
{
    AdjustByConv(*this, a.m_x, a.m_y);

    return (*this);
}

Point &Point::AdjustBy(int d_x, int d_y)
{
    AdjustByConv(*this, d_x, d_y);

    return (*this);
}

bool Point::IsEqual(Point a) const
{
    return (m_x == a.m_x && m_y == a.m_y);
}

static bool IsCalcLen(const Point &point)
{
    return (point.m_x == point.m_saved_x && point.m_y == point.m_saved_y);
}
 
double Point::Len() const
{
    if (!IsCalcLen(*this))
    {
        m_saved_x = m_x;
        m_saved_x = m_y;
        g_total_len -= m_point_len;
        m_point_len = sqrt(m_x * m_x + m_y * m_y); 
        g_total_len += m_point_len;
    }
    
    return (m_point_len); 
} 

void Point::Print(char open, char close) const
{
    std::cout << open << m_x << "," << m_y << close << '\n';
}

void Point::Print(ParenthesesType pare) const
{
    const char *open_lut = "([{<";
    const char *close_lut = ")]}>";

    const char open = open_lut[pare];
    const char close = close_lut[pare];

    Print(open, close);
}

Point Add(const Point a, const Point b) 
{
    Point ret;
    ret.m_x = a.m_x + b.m_x;
    ret.m_y = a.m_y + b.m_y;
    ret.AdjustToLimit();

    return (ret);
}

void Point::AdjustToLimit()
{
    m_x %= m_max_limit;
    m_y %= m_max_limit;
}

Point::Point()
    : m_x(2), m_y(2), m_saved_x(2), m_saved_y(2), 
    m_point_len(sqrt(m_x * m_x + m_y * m_y)), m_max_limit(100)
{
    g_total_len += m_point_len;
}

Point::Point(int p_x, int p_y, int limit)
    : m_x(p_x), m_y(p_y), m_saved_x(p_x), m_saved_y(p_y),
    m_point_len(sqrt(m_x * m_x + m_y * m_y)), m_max_limit(limit)
{
    g_total_len += m_point_len;
}

Point::~Point()
{
    g_total_len -= m_point_len;
}

double TotalLen()
{
    return (g_total_len);
} 

Point& Point::operator=(const Point& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_saved_x = other.m_saved_x;
    m_saved_y = other.m_saved_y;
    m_point_len = other.m_point_len;
    m_max_limit = other.m_max_limit;

    return (*this);
}



