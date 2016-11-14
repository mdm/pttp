#include <iostream>
#include <SDL.h>

#include "window.h"
#include "renderer.h"
#include "quad.h"

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
            Renderer renderer;
            Quad* quad = new Quad(200, 200, 0.4);
            glm::mat4 translate = glm::translate(glm::vec3(50.0f, 50.0f, 0.0f));
            glm::mat4 rotate = glm::rotate(3.1415926f / 4, glm::vec3(0.0f, 0.0f, 1.0f));
            //rotate = glm::mat4();
            quad->setTransform(translate * rotate);
            renderer.addQuad(quad);
            quad = new Quad(100, 100, 0.2f);
            renderer.addQuad(quad);
            bool quit = false;
            while(!quit)
            {
                renderer.renderFrame();
                window.Swap();

                SDL_Delay(8000);
                quit = true;
            }
        }
        SDL_Quit();
    }
    
    return 0;
}
