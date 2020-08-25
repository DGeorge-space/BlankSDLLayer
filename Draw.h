
#include "Screen.h"

class Draw
{

private:


public:
    Uint32 lifetime;

    Uint8 red;
    Uint8 green;

    Uint8 blue;
    int born;

    bool isAlive;

    vector<int> xVals;

    vector<int> yVals;
    int number;

public:
    Draw();
    
    void setlifetime(int lifeTimeInTicks);
    void checkAlive();
    void kill();
    void setColours();
    void setColours(int red, int green, int blue);
    void reduceCol();
    void output(Screen screen);
    ~Draw();
};

Draw::Draw()
{
    lifetime = rand() % 2000+1;
    isAlive= true;
    born= SDL_GetTicks();
    
    setColours();
    xVals;
    yVals;
}

void Draw::setlifetime(int lifeTimeInTicks)
{
    lifetime = lifeTimeInTicks;
}

void Draw::checkAlive(){
    if(lifetime<SDL_GetTicks()-born){
        kill();

    }
}

void Draw::kill(){
    isAlive=false;
    setColours(0,0,0);
}



void Draw::setColours()
{

    int randR = rand() % 100 + 100;
    int randG = rand() % 155 + 100;
    int randB = rand() % 155 + 100;
    green = randG;
    red = randR;
    blue = randB;
}
void Draw::setColours(int redInt, int greenInt, int blueInt)
{
    this->red = redInt;
    this->blue = blueInt;
    this->green = greenInt;
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
