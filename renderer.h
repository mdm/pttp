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
};

#endif // RENDERER_H
