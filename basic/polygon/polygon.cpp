#include <iostream> //size_t

#include "point.h"
#include "polygon.hpp"

Polygon::Polygon(size_t numPoints)
: m_numPoints(numPoints)
{
    m_points = new Point[numPoints + 1];
}

Polygon::~Polygon()
{
    delete[] m_points;
}

Polygon::Polygon(const Polygon& other)
: m_numPoints(other.m_numPoints), m_points (new Point[other.m_numPoints])
{
    CpyArray(m_points, other.m_points, m_numPoints);
}

void Polygon::CpyArray(Point *dest, Point *src, size_t numPoints)
{
    for (size_t i = 0; i < numPoints; ++i)
    {
        dest[i] = src[i];
    }
}

Polygon& Polygon::operator=(const Polygon& other)
{
    delete[] m_points;
    m_numPoints = other.m_numPoints;
    m_points = new Point[other.m_numPoints];
    CpyArray(m_points, other.m_points, m_numPoints);

   return (*this);
}

void Polygon::Add(const Point& p)
{
    ++m_numPoints;
    Point *cpy_m_points = new Point[m_numPoints+1];
    CpyArray(cpy_m_points, m_points, m_numPoints);
    cpy_m_points[m_numPoints-1] = p;

    delete[] m_points;
    m_points = new Point[m_numPoints+1];
    CpyArray(m_points, cpy_m_points, m_numPoints);

    delete[] cpy_m_points;
}

bool Polygon::IsPointArrEqual(Point *p1, Point *p2, size_t numPoints) const
{
    for (size_t i = 0; i < numPoints; ++i)
    {
        if (!p1[i].IsEqual(p2[i]))
        {
            return (false);
        }
    }

    return (true);
}

bool Polygon::IsEqual(const Polygon& p) const
{
    if (m_numPoints != p.m_numPoints)
    {
        return (false);
    }

    return (IsPointArrEqual(m_points, p.m_points, m_numPoints));
}

void Polygon::Print() const
{
    std::cout << std::endl << "m_numPoints: " << m_numPoints << std::endl;
    
    for (size_t i = 0; i < m_numPoints; ++i)
    { 
        std::cout << "point number " << i << ": " << std::endl;
        m_points[i].Print(); 
    }
}

