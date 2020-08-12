#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h> // outputs SDL errors!

using namespace std;

const int ScreenWidth = 800;
const int halfScreenWidth = ScreenWidth / 2;
const int ScreenHeight = 600;

bool init();

bool loadMedia();

SDL_Window *window = NULL; //The Window we are rendering to:

SDL_Surface *screenSurface = NULL; //The surface that renders to the window

SDL_Surface *xOut = NULL;

bool init()
{
    //Init flag:
    bool success = true;

    //Initialise SDL

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // when theres an error SDL_init returns -1
        // SDL_INIT_VIDEO will initialise the video component of SDL, There is also audio amongst others

        printf("SDL could not Initialise! SDL_ERROR: %s\n", SDL_GetError());
        //printf does printed formtting where %s is the placeholder for the SDL_GgetError()
    }
    else
    {
        //create the window
        window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError);
            //this will output a different error to the one above
            success = false;
        }
        else
        {
            //get window Surface
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool loadMedia()
{
    //loading success
    bool success = true;

    //load spash image
    xOut = SDL_LoadBMP("x.bmp");
    if (xOut == NULL)
    {
        printf("Unable to load image $s SDL Error: %s\n", "x.bpm", SDL_GetError());
        success = false;
    }
    return success;
}

void close()
{
    //deallocate surface frm memory
    SDL_FreeSurface(xOut);
    xOut = NULL;

    //Destroy Window
    SDL_DestroyWindow(window);
    window = NULL;

    //Quit SDL
    SDL_Quit();
}

//The parameters in the main function cannot be omitted, or an error will be reported
int main(int arg, char *argv[])
{
    if (!init())
    {
        printf("Failed to init \n");
    }
    else
    {
        //load media
        if (!loadMedia())
        {
            printf("Failed to load Media \n");
        }
        else
        {
            bool quit = false;

            SDL_Event event;

            while (!quit)
            {

                //Handle events in event queue
                while (SDL_PollEvent(&event) != 0)
                {
                    //user requests quit
                    if (event.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                SDL_BlitSurface(xOut, NULL, screenSurface, NULL);
                //output to the screen surface

                SDL_UpdateWindowSurface(window);
            }
        }

        close();

        return 0; // return zero means all is good
    }
}