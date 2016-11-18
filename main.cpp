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
            SDL_Event event;
            Renderer renderer;
            Quad* quad = new Quad(200, 200, 8);
            glm::mat4 translate = glm::translate(glm::vec3(100.0f, 100.0f, 0.0f));
            glm::mat4 rotate = glm::rotate(3.1415926f / 4, glm::vec3(0.0f, 0.0f, 1.0f));
            //rotate = glm::mat4();
            quad->setTransform(translate * rotate);
            renderer.addQuad(quad);
            quad = new Quad(100, 100, 10);
            quad->setTransform(translate * rotate);
            renderer.addQuad(quad);//*/
            bool quit = false;
            float angleRadians = 3.1415926f / 4;
            while(!quit)
            {
                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT)
                {
                    quit = true;
                }
                renderer.renderFrame();
                window.Swap();
                angleRadians += 0.001f;
                if(angleRadians > 2 * 3.1415926f)
                {
                    angleRadians = 0.0f;
                    //quit = true;
                }
                rotate = glm::rotate(angleRadians, glm::vec3(0.0f, 0.0f, 1.0f));
                quad->setTransform(translate * rotate);

                //SDL_Delay(8000);
                //quit = true;
            }
        }
        SDL_Quit();
    }
    
    return 0;
}
