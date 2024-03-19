#ifndef ILRD_RD61_SHAPE_HPP
#define ILRD_RD61_SHAPE_HPP

#include <iostream>
#include "glut_utils.h" //colors
#include "point.hpp" //point

namespace ilrd
{

class Shape
{
public:
    explicit Shape(); 
    explicit Shape(Point center, double angle, COLORS color); 
    virtual ~Shape() { std::cout << __func__ << std::endl; }
    //defult cctor
    //defult assignmant
    virtual COLORS GetColor() const;
    virtual Point GetCenter() const;
    virtual Shape& Move(Point toMove);
    virtual Shape& Move(double x, double y);
    virtual Shape& Revolve(Point pivot, double angle);
    virtual Shape& Rotate(double angle);
    virtual double GetAngle() const;
    virtual void Draw() const {}
    void SetColor(COLORS color);
    Point& ChangeCenter(Point newCenter);
    Point SetPoint(int xDelta, int yDelta) const; 

private:
    Point m_center;
    double m_angle;
    COLORS m_color;
};


} //namespae ilrd
#endif // SHAPE

