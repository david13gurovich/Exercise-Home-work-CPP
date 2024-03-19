#ifndef ILRD_RD61_RECTANGLE_HPP
#define ILRD_RD61_RECTANGLE_HPP

#include <iostream>
#include "shape.hpp" //point, color

namespace ilrd
{

class Rectangle: public Shape
{
public:
    explicit Rectangle(Point center, double angle, COLORS color, 
                                size_t longSide, size_t shortSide); 
    virtual ~Rectangle(){ std::cout << __func__ << std::endl; }
    //Rectangle(const Rectangle& other) = defult
    //Rectangle& operator=(const Rectangle& other) = defult
    virtual void Draw() const;
    size_t GetLongSide() const;
    size_t GetShortSide() const;

private:
    size_t m_longSide;
    size_t m_shortSide;
};

} //namespae ilrd
#endif // RECTANGLE

