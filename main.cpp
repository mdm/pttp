#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "window.h"
#include "renderer.h"
#include "quad.h"
#include "level.h"

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Could not init SDL: " << SDL_GetError() << std::endl;
    }
    else
    {
        IMG_Init(IMG_INIT_PNG);

        {
            Window window("Paint The Town Pink!");
            SDL_Event event;
            ResourceManager resourceManager;
            Renderer renderer(resourceManager);

            // test scene
            uint32_t checkerboard = resourceManager.makeQuad(200, 200, 8, resourceManager.makeCheckerboardTexture(200, 200, 10));
            glm::mat4 translate = glm::translate(glm::vec3(100.0f, 100.0f, 0.0f));
            glm::mat4 rotate = glm::rotate(3.1415926f / 4, glm::vec3(0.0f, 0.0f, 1.0f));
            resourceManager.getQuad(checkerboard)->setTransform(translate * rotate);

            uint32_t image = resourceManager.makeQuad(150, 150, 10, resourceManager.loadTextureFromPNG("test.png"));
            resourceManager.getQuad(image)->setTransform(translate * rotate);

            bool quit = false;
            float angleRadians = 3.1415926f / 4;

            Level level("original.lvl");
            std::cout << level.toString();

            uint32_t previousTimestamp = SDL_GetTicks();
            uint32_t lag = 0;
            while(!quit)
            {
                uint32_t currentTimestamp = SDL_GetTicks();
                lag += currentTimestamp - previousTimestamp;
                previousTimestamp = currentTimestamp;

                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT)
                {
                    quit = true;
                }

                while(lag >= 16) {
                    angleRadians += 0.01f;
                    if(angleRadians > 2 * 3.1415926f)
                    {
                        angleRadians = 0.0f;
                    }
                    rotate = glm::rotate(angleRadians, glm::vec3(0.0f, 0.0f, 1.0f));
                    resourceManager.getQuad(image)->setTransform(translate * rotate);

                    lag -= 16;
                }

                renderer.addQuad(checkerboard);
                renderer.addQuad(image);
                renderer.renderFrame();
                window.Swap();
            }
        }
        SDL_Quit();
    }
    
    return 0;
}
