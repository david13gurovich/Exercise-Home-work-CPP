#include <iostream>
#include "line.hpp"

namespace ilrd
{

Line::Line(Point center, double angle, COLORS color, size_t lineLen)
: Shape(center, angle, color), m_lineLen(lineLen)
{}

size_t Line::GetLineLen() const 
{
    return (m_lineLen);
}

void Line::Draw() const
{
    int nPoints = 2;
    size_t lineLen = GetLineLen() / 2;

    Point firstPoint = SetPoint(-lineLen, 0);
    Point secondPoint = SetPoint(lineLen, 0);

    int firstPointX = firstPoint.GetX();
    int firstPointY = firstPoint.GetY();
    int secondPointX = secondPoint.GetX();
    int secondPointY =  secondPoint.GetY();

    DrawPolygon(GetColor(), nPoints, firstPointX, firstPointY, 
                                    secondPointX, secondPointY); 
}

}//namespace irld