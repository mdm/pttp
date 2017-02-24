#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <GL/glew.h>

#include "resource_manager.h"
#include "quad.h"

class Renderer
{
public:
    Renderer(ResourceManager& resourceManager);
    ~Renderer();

    void addQuad(uint32_t quad);
    void renderFrame();

private:
    ResourceManager& _resourceManager;
    static const char* vertexShaderSource;
    static const char* fragmentShaderSource; 

    GLuint _shaderProgram;
    std::vector<uint32_t> _quads;
    std::map<uint32_t, GLuint> _textures;

    clock_t _startTime;
    int _framesRendered;
};

#endif // RENDERER_H
