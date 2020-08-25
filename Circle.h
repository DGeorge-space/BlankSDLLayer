#include "Draw.h"
#include <vector>

class Circle : public Draw
{
private:
    int x;
    int y;
    int radius;

    Screen screenTEMP;
    const float PI = 3.14159265;

public:
    Circle();
    int getX();
    int getY();
    int getRadius();
    Circle(int x, int y, int radius);
    void constructCircle();

    ~Circle();
};


Circle::Circle()
{
    x = rand() % screenTEMP.ScreenWidth;
    y = rand() % screenTEMP.ScreenHeight;

    radius = rand() % 20 + 10;

    constructCircle();
}
Circle::Circle(int x, int y, int radius)
{
    this->x = x;
    this->y = y;
    this->radius = radius;

    constructCircle();
}

int Circle::getX(){
    
    return this->x;
}

int Circle::getY(){
    
    return this->y;
}
int Circle::getRadius(){
    return this->radius;
}

void Circle::constructCircle()
{

    for (int i = 0; i < 361; i++)
    {
        int xp = x + radius * cos((i * PI) / 180);
        int yp = y + radius * sin((i * PI) / 180);

        xVals.push_back(xp);
        yVals.push_back(yp);
    }
}
