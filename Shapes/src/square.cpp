#include "square.hpp"

namespace ilrd
{

Square::Square(Point center, double angle, COLORS color, size_t sideLen)
: Rectangle(center, angle, color, sideLen, sideLen)
{}

size_t Square::GetSideLen() const
{
	return (m_SideLen);
}

}//namespace irld