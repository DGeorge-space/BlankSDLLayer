
#include "Screen.h"

class Draw
{

private:
    Uint32 lifetime;
    const int dimming = 50;
    Uint8 red;
    Uint8 green;

    Uint8 blue;

public:
    int born = SDL_GetTicks();

    bool isAlive = true;

    vector<int> xVals;

    vector<int> yVals;
    int number;

public:
    Draw();
    
    void setlifetime(int lifeTimeInTicks);
    void circle(int x, int y, int radius);
    void checkAlive();
    void setColours();
    void setColours(int red, int green, int blue);
    void reduceCol();
    void output(Screen screen);
    ~Draw();
};

Draw::Draw()
{
    int randLifetime = rand() % 2000;
    setlifetime(500);
    
    setColours();
    xVals;
    yVals;
}

void Draw::setlifetime(int lifeTimeInTicks)
{
    lifetime = lifeTimeInTicks;
}

void Draw::checkAlive(){
    if(lifetime>SDL_GetTicks()-born){
        isAlive=false;
    }
}

void Draw::circle(int x, int y, int radius)
{
    const float PI = 3.14159265;

    for (int i = 0; i < 361; i++)
    {
        int xp = x + radius * cos((i * PI) / 180);
        int yp = y + radius * sin((i * PI) / 180);

        xVals.push_back(xp);
        yVals.push_back(yp);
    }
}

void Draw::setColours()
{

    int randR = rand() % 256 + 1;
    int randG = rand() % 256 + 1;
    int randB = rand() % 256 + 1;
    green = randG;
    red = randR;
    blue = randB;
}
void Draw::setColours(int redInt, int greenInt, int blueInt)
{
    red = redInt;
    blue = blueInt;
    green = greenInt;
}

void Draw::reduceCol()
{
    if (SDL_GetTicks() - born > lifetime)
    {
        while (red > 0 || green > 0 || blue > 0)
        {
            if (red > 0)
            {
                red--;
                setColours(red,green,blue);
            }
            if (green > 0)
            {
                green--;
                setColours(red,green,blue);
            }
            if (blue > 0)
            {
                blue--;
                setColours(red,green,blue);
            }
            
 
        }
    }
}

void Draw::output(Screen screen)
{
    // if (red == NULL || green == NULL || blue == NULL)
    // {
    //     setColours();
    // }

    for (int i = 0; i < xVals.size(); i ++)
    {
        int alive = int(SDL_GetTicks) - born;
        screen.setPixel(xVals[i], yVals[i], red, green, blue);
    }
    screen.update();
}
Draw::~Draw(){};
