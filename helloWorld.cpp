#include "Circle.h"

#include <iostream>

using namespace std;

//The parameters in the main function cannot be omitted, or an error will be reported
int main(int arg, char *argv[])
{
    int numCircles = 500;
    Circle *circles[numCircles];
    Screen screen;
    screen.init();

    for (int i = 0; i < numCircles; i++)
    {
        circles[i] = new Circle();

    }
    while (true)
    {
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

        if (screen.processEvents() == false)
        {
            break;
        }
        
        
        screen.update();
        //screen.boxBlur();
    }
    
    return 0; // return zero means all is good
    screen.close();
    
}
