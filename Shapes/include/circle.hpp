#ifndef ILRD_RD61_CIRCLE_HPP
#define ILRD_RD61_CIRCLE_HPP

#include "shape.hpp" //point, color

namespace ilrd
{

class Circle : public Shape
{
public:
    explicit Circle(Point center, double angle, COLORS color, double m_radius); 
    virtual ~Circle() { std::cout << __func__ << std::endl; }
    //Circle(const Circle& other) = defult
    //Circle& operator=(const Circle& other) = defult
    virtual void Draw() const;
    double GetRadius() const;

private:
    double m_radius;
};

} //namespae ilrd
#endif // CIRCLE

