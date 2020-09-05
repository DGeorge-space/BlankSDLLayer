
#include <iostream>
#include <stdio.h> // outputs SDL errors!
#include <math.h>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class Screen
{
public:
    const static int ScreenHeight = 800;
    const static int ScreenWidth = 1000;

private:
    SDL_Window *window; //The Window we are rendering to:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Uint32 *buffer1;
    Uint32 *buffer2;

    SDL_Surface *screenSurface; //The surface that renders to the window

    SDL_Surface *xOut;

public:
    Screen();
    bool init();
    void update();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    bool processEvents();
    void close();
    
    bool loadMedia(char relativeMediaDirectory[]);
};
//ugjgjg


Screen::Screen() : window(NULL), renderer(NULL), texture(NULL), buffer1(NULL), buffer2(NULL) {}

bool Screen::init()
{
    //Init flag:

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
        window = SDL_CreateWindow("Circles everywhere", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError);
            //this will output a different error to the one above
            return false;
        }

        //get window Surface
        screenSurface = SDL_GetWindowSurface(window);

        //create renderer & conditions
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

        //Create the texture to be put on the renderer
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, ScreenWidth, ScreenHeight);

        if (renderer == NULL)
        {
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        if (texture == NULL)
        {
            SDL_DestroyWindow(window);
            SDL_Quit;
            return false;
        }
        // The buffers will prepare our screen to be updated
        buffer1 = new Uint32[ScreenWidth * ScreenHeight];
        buffer2 = new Uint32[ScreenWidth * ScreenHeight];
    }
    //Memset will allocate the memory for each pixel
    memset(buffer1, 0, ScreenHeight * ScreenWidth * sizeof(Uint32));
    memset(buffer2, 0, ScreenHeight * ScreenWidth * sizeof(Uint32));

    return true;
}

bool Screen::loadMedia(char relativeMediaDirectory[])
{
    //loading success
    bool success = true;

    //load spash image
    xOut = SDL_LoadBMP(relativeMediaDirectory);
    if (xOut == NULL)
    {
        printf("Unable to load image $s SDL Error: %s\n", "x.bpm", SDL_GetError());
        success = false;
    }
    return success;
}
void Screen::update()
{
    //refresh the screen
    SDL_UpdateTexture(texture, NULL, buffer1, ScreenWidth * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
    //stops plotting off the screen bounds~ can be problematic since this means memory is being accessed that shouldn't be
    if (x < 0 || x >= ScreenWidth || y < 0 || y >= ScreenHeight)
    {
        return;
    }
    Uint32 color = 0;
    color<<=8;
    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;


    buffer1[(y * ScreenWidth) + x] = color;
}

bool Screen::processEvents()
{//does event handling for inputs, currently the only event is to quit
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }
    }
    return true;
}


void Screen::close()
{
    

    //deallocate surface frm memory
    SDL_FreeSurface(xOut);


    xOut = NULL;

    //Destroy Window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    window = NULL;

    delete[] buffer1;
    delete[] buffer2;

    //Quit SDL
    SDL_Quit();
}