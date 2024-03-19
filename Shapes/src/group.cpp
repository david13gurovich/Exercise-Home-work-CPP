#include <iostream>
#include "group.hpp"

namespace ilrd
{

Group& Group::Move(Point toMove)
{    
    int deltaX = toMove.GetX() - GetCenter().GetX();
    int deltaY = toMove.GetY() - GetCenter().GetY();
    Move(deltaX, deltaY);
    
    SetCenter();

    return (*this);
}

Group& Group::Move(double x, double y)
{
    int size = shapeVector.size();
    
    for(int i = 0; i < size; ++i)
    {
       shapeVector[i]->Move(x, y);
    }

    return (*this);
}

Group& Group::Revolve(Point pivot, double angle)
{
    return (Move(GetCenter().Revolve(pivot, angle)));
}

Group& Group::Rotate(double angle)
{
    Point pivot = GetCenter();
    int size = shapeVector.size();
     
    for(int i = 0; i < size; ++i)
    {
       shapeVector[i]->Rotate(angle);
       shapeVector[i]->Revolve(pivot, angle);
    } 

    return (*this);
}

void Group::Draw() const
{
    int size = shapeVector.size();
    
    for(int i = 0; i < size; ++i)
    {
       shapeVector[i]->Draw();
    }
}

void Group::SetColor(COLORS color)
{
    int size = shapeVector.size();
    
    for(int i = 0; i < size; ++i)
    {
       shapeVector[i]->SetColor(color);
    }
}

void Group::AddShape(Shape *toAdd)
{
    shapeVector.push_back(toAdd);
    SetCenter();
}

void Group::SetCenter()
{
    int sumGetX = 0;
    int sumGetY = 0;
    int size = shapeVector.size();
    
    for(int i = 0; i < size; ++i)
    {
       sumGetX += shapeVector[i]->GetCenter().GetX();
       sumGetY += shapeVector[i]->GetCenter().GetY();
    }

    sumGetX /= size;
    sumGetY /= size;
    Point newCenter(sumGetX, sumGetY);
    ChangeCenter(newCenter);
}

} //namespae ilrd