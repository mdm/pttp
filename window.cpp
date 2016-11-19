#include <SDL.h>
#include <iostream>

#include "window.h"

Window::Window(const std::string& title)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    _window = SDL_CreateWindow(title.c_str(),
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               800,
                               600,
                               SDL_WINDOW_OPENGL);

    _context = SDL_GL_CreateContext(_window);

    int attrValue;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &attrValue);
    std::cout << attrValue << std::endl;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &attrValue);
    std::cout << attrValue << std::endl;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &attrValue);
    std::cout << (attrValue == SDL_GL_CONTEXT_PROFILE_CORE) << std::endl;
}

Window::~Window()
{
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
}

void Window::Swap()
{
    SDL_GL_SwapWindow(_window);
}
