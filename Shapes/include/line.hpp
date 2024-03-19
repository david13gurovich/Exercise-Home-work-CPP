#ifndef ILRD_RD61_LINE_HPP
#define ILRD_RD61_LINE_HPP

#include "shape.hpp" //point, color

namespace ilrd
{

class Line : public Shape
{
public:
    explicit Line(Point center, double angle, COLORS color, size_t lineLen); 
    ~Line() {}
    //defult cctor
    //defult assignmant
    virtual void Draw() const;
    size_t GetLineLen() const;

private:
    size_t m_lineLen;
};

} //namespae ilrd
#endif // LINE

