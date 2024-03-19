#include <ctime> //srand
#include <iostream>

#include "shape.hpp"
#include "line.hpp"
#include "circle.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "group.hpp"

using namespace ilrd;

Line g_line(Point(100, 100), 0, COLOR_CYAN, 100);
Circle g_circle(Point(100, 240), 300, COLOR_RED, 100);
Square g_square(Point(200 ,400), 100, COLOR_WHITE, 200);
Rectangle g_rectangle(Point(700, 400), 0, COLOR_YELLOW, 200, 500);

Group g_train;
Group g_wheels1;
Group g_wheels2;

Line line1 = Line(Point(700, 500), 30, COLOR_CYAN, 135);
Line line2 = Line(Point(700, 500), 0, COLOR_CYAN, 135);
Line line3 = Line(Point(220, 500), 30, COLOR_CYAN, 135);
Line line4 = Line(Point(220, 500), 0, COLOR_CYAN, 135); 

static void DrawFunction()
{
    // g_line.Draw();
    // g_circle.Draw();
    // g_square.Draw();
    // g_rectangle.Draw();
    // g_wheels1.Draw();
    // g_wheels2.Draw();

    g_train.Draw();
    line1.Draw();
    line2.Draw();
    line3.Draw();
    line4.Draw();
}

int g_circleInterval = 1;
int g_groupInterval = 2;

static int TimerFunction()
{
    // g_circle.Move(g_circleInterval, g_circleInterval);
    // ++g_circleInterval;
    
    // if (g_circle.GetCenter().GetX() >= 900)
    // {
    //    g_circleInterval *= -1; 
    // }

    // g_line.Rotate(g_line.GetAngle() + 1);
    // g_square.Revolve(Point(500, 500), 1);
    // g_rectangle.Move(1, 1);

    // g_group.Revolve(Point(150, 150), 0.5);
    // g_group.Rotate(g_group.GetAngle() + 1);
    
    g_train.Move(g_groupInterval, 0); 
    
    g_wheels1.Rotate(1);
    g_wheels2.Rotate(1);

    line1.Move(g_groupInterval, 0);
    line2.Move(g_groupInterval, 0);
    line3.Move(g_groupInterval, 0);
    line4.Move(g_groupInterval, 0);
    
    line1.Rotate(5);
    line2.Rotate(5);
    line3.Rotate(5);
    line4.Rotate(5);

    ++g_groupInterval;

    if(line4.GetCenter().GetX() >= 900 || line4.GetCenter().GetX() <= 100)
    {
        g_groupInterval *= -1;
    }

    return 1;  
}

static int MouseFunction(int button, int state, int x, int y)
{
    (void)state;
    (void)x;
    (void)y;

    if (button == MOUSE_LEFT)
    {
        g_train.SetColor(static_cast<COLORS>(COLOR_BLUE));
        return (1);
    }

    if (button == MOUSE_RIGHT)
    {
        g_train.SetColor(static_cast<COLORS>(COLOR_YELLOW));
        
        return (1);
    }

    return (0);
}

int main(int argc, char *argv[])
{
    Circle wheel1 = Circle(Point(220, 500), 0, COLOR_CYAN, 70);
    Circle wheel2 = Circle(Point(700, 500), 0, COLOR_CYAN, 70);
    Square window1 = Square(Point(250, 200), 0, COLOR_RED, 100);
    Square window2 = Square(Point(450, 200), 0, COLOR_YELLOW, 100);
    Square window3 = Square(Point(700, 200), 0, COLOR_GREEN, 100);
    Rectangle body = Rectangle(Point(450, 250), 0, COLOR_BLUE, 700, 450);
    
    g_train.AddShape(&wheel1);
    g_train.AddShape(&wheel2);
    g_train.AddShape(&window1); 
    g_train.AddShape(&window2); 
    g_train.AddShape(&window3); 
    g_train.AddShape(&body);

    DrawInit(argc, argv, 1000, 1000, DrawFunction);  
    DrawSetTimerFunc(TimerFunction, 100);
    DrawSetMouseFunc(MouseFunction);
    DrawMainLoop();

    return 0;
}
