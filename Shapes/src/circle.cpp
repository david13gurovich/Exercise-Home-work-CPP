#include "circle.hpp"

namespace ilrd
{

Circle::Circle(Point center, double angle, COLORS color, double radius)
: Shape(center, angle, color), m_radius(radius)
{}

double Circle::GetRadius() const
{
    return (m_radius);
}

void Circle::Draw() const
{
	int xCircle = GetCenter().GetX();
	int yCircle = GetCenter().GetY();
	double rCircle = GetRadius();
	
	DrawCircle(GetColor(), xCircle, yCircle, rCircle);
}

}//namespace irld