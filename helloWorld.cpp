#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h> // outputs SDL errors!
#include <math.h>

using namespace std;

SDL_Window *window = NULL; //The Window we are rendering to:

SDL_Surface *screenSurface = NULL; //The surface that renders to the window

SDL_Surface *xOut = NULL;
class Screen
{
public:
    const static int ScreenHeight = 800;
    const static int ScreenWidth = 600;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Uint32 *buffer1;
    Uint32 *buffer2;

public:
    Screen();
    bool init();
    void update();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    bool processEvents();
    void close();
    void boxBlur();
    bool loadMedia(char relativeMediaDirectory[]);
};

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
        window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
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
    //Memset will allocate the
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
    SDL_UpdateTexture(texture, NULL, buffer1, ScreenWidth * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
    //stops plotting off the screen bounds~ can be problematic
    if (x < 0 || x >= ScreenWidth || y < 0 || y >= ScreenHeight)
    {
        return;
    }
    Uint32 color = 0;
    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    buffer1[(y * ScreenWidth) + x] = color;
}

bool Screen::processEvents()
{
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
    delete[] buffer1;
    delete[] buffer2;

    xOut = NULL;

    //Destroy Window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    window = NULL;

    //Quit SDL
    SDL_Quit();
}

//The parameters in the main function cannot be omitted, or an error will be reported
int main(int arg, char *argv[])
{
    Screen screen;
    if (!screen.init())
    {
        printf("Failed to init \n");
    }
    else
    {
        while (true)
        {
            //update particles
            //draw particles
            int elapsed = SDL_GetTicks();

            //		screen.clear();

            unsigned char green = (1 + sin(elapsed * 0.05)) * 128;
            unsigned char red = (1 + cos(elapsed * 0.005)) * 128;
            unsigned char blue = (1 + sin(elapsed * 0.0007)) * 128;

            for (int i = 0; i < 500; i++)
            {

                int x = i;
                int y = i;

                screen.setPixel(x, y, red, green, blue);
                
                
                screen.update();
                
            }

            screen.update();
            if (screen.processEvents() == false)
            {
                break;
            }
        }

        screen.close();

        return 0; // return zero means all is good
    }
}
