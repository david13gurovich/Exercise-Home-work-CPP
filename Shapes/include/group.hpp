#ifndef ILRD_RD61_GROUP_HPP
#define ILRD_RD61_GROUP_HPP

#include <iostream>
#include <vector> 
#include "shape.hpp" //point, color

namespace ilrd
{

class Group: public Shape
{
public:
    explicit Group(){} //cant rely on defult ctor because there is a ctor non default to shape 
    ~Group() {std::cout << __func__ << std::endl;}
    virtual Group& Move(Point toMove);
    virtual Group& Move(double x, double y);
    virtual Group& Revolve(Point pivot, double angle);
    virtual Group& Rotate(double angle);
    virtual void Draw() const;
    virtual void SetColor(COLORS color);
    void SetCenter();
    void AddShape(Shape *toAdd);

private:
    std::vector<Shape*> shapeVector; 
    explicit Group(Group& other); //overwriting, we dont want because becuse there are pointers  
    Group& operator=(Group& other); //overwriting, we dont want because becuse there are pointers  
};

} //namespae ilrd
#endif // GROUP

