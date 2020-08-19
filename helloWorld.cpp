#include "Animate.h"

using namespace std;

//The parameters in the main function cannot be omitted, or an error will be reported
int main(int arg, char *argv[])
{
    Screen screen;
    screen.init();
    int numCircles = 10;
    Draw circle[numCircles];

    Draw corners[numCircles];

    for (int i = 0; i < numCircles; i++)
    {
        circle[i].setlifetime(100000000);
        corners[i].setlifetime(100);
        circle[i].circle(screen.ScreenWidth / 2, screen.ScreenHeight / 2, rand() % 200 + 50);
        corners[i].circle(screen.ScreenWidth / 4, screen.ScreenHeight / 4, rand() % 100 + 50);
        corners[i].circle(screen.ScreenWidth / 4, 3 * screen.ScreenHeight / 4, rand() % 100 + 50);
        corners[i].circle(3 * screen.ScreenWidth / 4, 3 * screen.ScreenHeight / 4, rand() % 100 + 50);
        corners[i].circle(3 * screen.ScreenWidth / 4, screen.ScreenHeight / 4, rand() % 100 + 50);
        circle[i].output(screen);
        corners[i].output(screen);
    }


    while (true)
    {

        for (int i = 0; i < numCircles; i++)
        {

            circle[i].checkAlive();
            corners[i].checkAlive();

            if (circle[i].isAlive==false)
            {
                circle[i].setColours(0, 0, 0);
                corners[i].setColours(0, 0, 0);
            }

            screen.update();
        

        circle[i].output(screen);
        corners[i].output(screen);
        }

        if (screen.processEvents() == false)
        {
            break;
        }
        // screen.boxBlur();
        SDL_Delay(300);
    }

    return 0; // return zero means all is good
    screen.close();
}
