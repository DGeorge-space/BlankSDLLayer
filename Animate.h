#include "Circle.h"

class Animate : public Circle
{
private:


int maxRad;
int numCircles;
static Circle *circles[numCircles];
public:
Screen screen;
public:
    void expandingCircle(Screen screen);
    Animate();
    void randomDraw();
    ~Animate();
};

Animate::Animate()
{
    
    numCircles = rand() % 100 + 1;
    for (int i = 0; i < numCircles; i++)
    {
        circles[i] = new Circle(); 
        
    }


}
void Animate::randomDraw(){
     for (int i = 0; i < numCircles; i++)
        {
            
            circles[i]->checkAlive();
            
            if(circles[i]->isAlive==false){
                circles[i]->output(screen);
                circles[i] = new Circle();
                
            }
            circles[i]->output(screen);
            screen.update();
            
        }
}

void Animate::expandingCircle(Screen screen)
{


    
    
     
}

Animate::~Animate()
{
    delete[] circles;

}