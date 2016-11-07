#include <iostream>
#include <GL/glew.h>
#include <SDL.h>

#include "window.h"

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Could not init SDL: " << SDL_GetError() << std::endl;
    }
    else
    {
        {
            Window window("Paint The Town Pink!");
            glewInit();
            bool quit = false;
            while(!quit)
            {
                glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                window.Swap();

                SDL_Delay(8000);
                quit = true;
            }
        }
        SDL_Quit();
    }
    
    return 0;
}
