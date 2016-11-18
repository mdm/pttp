#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <GL/glew.h>

#include "quad.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void addQuad(Quad* quad);
    void renderFrame();

private:
    static const char* vertexShaderSource;
    static const char* fragmentShaderSource; 

    GLuint _shaderProgram;
    std::vector<Quad*> _quads;

    clock_t _startTime;
    int _framesRendered;
};

#endif // RENDERER_H
