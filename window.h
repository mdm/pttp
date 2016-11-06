#ifndef WINDOW_H
#define WINDOW_H

#include <string>

class Window
{
public:
    Window(const std::string& title);
    ~Window();
    
    void Swap();

private:
    SDL_Window* _window;
    SDL_GLContext _context;
};

#endif // WINDOW_H
