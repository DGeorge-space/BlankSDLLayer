#include "Draw.h"

class Animate : Screen
{
private:
    Draw draw;
    int born=1000;

public:
    void expandingCircle(Screen screen);
    Animate();
    ~Animate();
};

Animate::Animate()
{
    Draw draw;
    //born = SDL_GetTicks();
    draw.setlifetime(100);


}

void Animate::expandingCircle(Screen screen)
{

    int randX = rand() % ScreenWidth + 1;
    int randY = rand() % ScreenHeight/2 +0 ;
    int randRad = rand() % 50 + 1;
    int itCount = 0;
    for (int i = 0; i < randRad; i++)
    {
        //int timeAlive= SDL_GetTicks()-born;
        draw.circle(randX, randY, i);
        draw.reduceCol();
        draw.output(screen);
        
         
    }
    
    draw.output(screen);
    
    
    
     
}

Animate::~Animate()
{

}