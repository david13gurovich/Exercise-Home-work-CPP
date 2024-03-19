#include "shape.hpp"

namespace ilrd
{

Shape::Shape(Point center, double angle, COLORS color)
: m_center(center), m_angle(angle), m_color(color)
{}

Shape::Shape()
: m_center(0,0), m_angle(0), m_color(COLOR_BLUE)
{}

COLORS Shape::GetColor() const
{
    return (m_color);
}

Point& Shape::ChangeCenter(Point newCenter)
{
    m_center = newCenter;

    return (m_center);
}

Point Shape::GetCenter() const
{
    return (m_center);
}

double Shape::GetAngle() const
{
    return (m_angle);
}

void Shape::SetColor(COLORS color)
{
    m_color = color;
}

Shape& Shape::Move(Point toMove)
{
    m_center = toMove;
    
    return (*this);
}

Shape& Shape::Move(double x, double y)
{
    Step(&m_center, x, y);

    return (*this);
}

Shape& Shape::Revolve(Point pivot, double angle)
{
    m_center.Revolve(pivot, angle);

    return (*this);
}

Shape& Shape::Rotate(double deltaAngle)
{
    m_angle += deltaAngle;

    return (*this);
}

Point Shape::SetPoint(int xDelta, int yDelta) const
{
    Point center = GetCenter();
    double angle = GetAngle();
    int x = center.GetX() + xDelta;
    int y = center.GetY() + yDelta;
    Point toReturn(x, y);
    toReturn.Revolve(center, angle);

    return (toReturn);    
}

}//namespace irld