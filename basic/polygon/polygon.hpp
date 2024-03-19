#ifndef ILRD_RD61_POLYGON_HPP
#define ILRD_RD61_POLYGON_HPP

//#include "point.hpp"

struct Polygon 
{
    explicit Polygon(size_t numPoints = 0);  
    Polygon(const Polygon& other);
    Polygon& operator=(const Polygon& other);
    ~Polygon();

    void Add(const Point& p); 
    bool IsEqual(const Polygon& p) const; 
    void Print() const;

    size_t m_numPoints;
    Point *m_points;

    //NOT PART FROM THE API //
    void CpyArray(Point *dest, Point *src, size_t numPoints);
    bool IsPointArrEqual(Point *p1, Point *p2, size_t numPoints) const;
};

#endif
