#include "rectangle.hpp"

namespace ilrd
{

Rectangle::Rectangle(Point center, double angle, COLORS color, size_t longSide, 
                                                            size_t shortSide)
: Shape(center, angle, color), m_longSide(longSide), m_shortSide(shortSide)
{}

void Rectangle::Draw() const
{
    const int longSide = GetLongSide() / 2;
    const int shortSide = GetShortSide() / 2; 
	int nPoints = 4;

    Point firstPoint = SetPoint(-longSide, shortSide);
    Point secondPoint = SetPoint(longSide, shortSide);
    Point thirdPoint = SetPoint(longSide, -shortSide);
    Point forthPoint = SetPoint(-longSide, -shortSide);

    int firstPointX = firstPoint.GetX();
    int firstPointY = firstPoint.GetY();
    int secondPointX = secondPoint.GetX(); 
    int secondPointY = secondPoint.GetY();
    int thirdPointX = thirdPoint.GetX();
    int thirdPointY = thirdPoint.GetY();
    int forthPointX = forthPoint.GetX(); 
    int forthPointY = forthPoint.GetY();

    DrawPolygon(GetColor(), nPoints, firstPointX,firstPointY, 
                            secondPointX, secondPointY, 
    						thirdPointX, thirdPointY, 
                            forthPointX, forthPointY);
}

size_t Rectangle::GetLongSide() const
{
	return (m_longSide);
}

size_t Rectangle::GetShortSide() const
{
	return (m_shortSide);
}

}//namespace irld