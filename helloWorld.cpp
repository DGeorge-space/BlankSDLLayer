#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>// outputs SDL errors!


using namespace std;

const int ScreenWidth=600;
const int halfScreenWidth=ScreenWidth/2;
const int ScreenHeight = 800;

//The parameters in the main function cannot be omitted, or an error will be reported
int main(int arg, char *argv[])
{
    SDL_Window *window = NULL; //The Window we are rendering to:

    SDL_Surface *screenSurface = NULL;//The surface that renders to the window
    
    //Initialise SDL

    if(SDL_Init(SDL_INIT_VIDEO)<0){
        // when theres an error SDL_init returns -1
        // SDL_INIT_VIDEO will initialise the video component of SDL, There is also audio amongst others

        printf ("SDL could not Initialise! SDL_ERROR: %s\n", SDL_GetError());
        //printf does printed formtting where %s is the placeholder for the SDL_GgetError()
    }
    else{
        //create the window
        window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED,     SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
        // (nameOfWindow, xPosOnScreen, yPosOnScreen, width, Height, ShowsWindow)
        if(window ==NULL){
            printf ("Window could not be created! SDL_Error: %s\n", SDL_GetError);
            //this will output a different error to the one above 
        }else{
            //Define window surface
            screenSurface = SDL_GetWindowSurface(window);

            SDL_FillRect(screenSurface,NULL, SDL_MapRGBA(screenSurface-> format, 0xFF, 0xFF,0xFF, 1.0));//Fill White

            SDL_UpdateWindowSurface(window); // update the surface

            SDL_Delay(2000); // delay 2000 ms

            SDL_DestroyWindow(window); // destroy the window

            SDL_Quit(); //QUIT SDL 

            return 0; // return zero means all is good       
        }

    }

}//complete layoutdkhdkdh