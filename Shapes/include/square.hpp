#ifndef ILRD_RD61_SQUARE_HPP
#define ILRD_RD61_SQUARE_HPP

#include "rectangle.hpp" //point, color

namespace ilrd
{

class Square : public Rectangle
{
public:
    explicit Square(Point center, double angle, COLORS color, size_t SideLen); 
    ~Square() {}
    //defult cctor
    //defult assignmant
    size_t GetSideLen() const;

private:
    size_t m_SideLen;
};

} //namespae ilrd
#endif // LINE

