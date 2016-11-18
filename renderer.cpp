#include <iostream>

#include "renderer.h"

const char* Renderer::vertexShaderSource = 
"#version 330 core\n"
"in vec4 vertex;\n"
"in vec2 texCoordIn;\n"
"uniform mat4 modelView;\n"
"uniform mat4 projection;\n"
"out vec2 texCoord;\n"
"void main() {\n"
"   texCoord = texCoordIn;\n"
"   gl_Position = projection * modelView * vertex;\n"
"}\n";

const char* Renderer::fragmentShaderSource = 
"#version 330 core\n"
"uniform sampler2D tex;\n"
"in vec2 texCoord;\n"
"out vec4 color;\n"
"void main() {\n"
"    color = texture(tex, texCoord);\n"
"}\n";

Renderer::Renderer()
{
    _framesRendered = 0;

    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // set up shaders
    GLuint vertexShader, fragmentShader;
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    
    int len;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0)
    {
        char* log = new char[len];
        glGetShaderInfoLog(vertexShader, len, NULL, log);
        std::cout << log << std::endl;
        delete[] log;
    }
    
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    
    glLinkProgram(_shaderProgram);
    glUseProgram(_shaderProgram);

    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // set up buffers
    GLuint buffers[2];
    glGenBuffers(2, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Quad::vertices), Quad::vertices, GL_STATIC_DRAW);
    GLint vertexLoc = glGetAttribLocation(_shaderProgram, "vertex");
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Quad::texCoords), Quad::texCoords, GL_STATIC_DRAW);
    GLint texCoordLoc = glGetAttribLocation(_shaderProgram, "texCoordIn");
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(texCoordLoc);
}

Renderer::~Renderer()
{
    for(auto quad : _quads)
    {
        delete quad;
    }
}

void Renderer::addQuad(Quad* quad)
{
    // set up texture
    GLuint texture;
    glGenTextures(1, &texture);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, quad->getWidth(), quad->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, quad->getTexture());
    
    quad->setHandle(texture);
    _quads.push_back(quad);
}

void Renderer::renderFrame()
{
    if(_framesRendered == 0)
    {
        _startTime = clock();
    }

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto quad : _quads)
    {
        glBindTexture(GL_TEXTURE_2D, quad->getHandle());

        // set up matrix uniforms
        GLint modelViewLoc = glGetUniformLocation(_shaderProgram, "modelView");
        glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, glm::value_ptr(quad->getTransform()));
        GLint projectionLoc = glGetUniformLocation(_shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 100.0f, 0.0f)));

        // draw the quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // TODO: delete buffers ???
    }//*/

    ++_framesRendered;
    clock_t elapsedTime = clock() - _startTime;
    if(elapsedTime >= CLOCKS_PER_SEC)
    {
        std::cout << _framesRendered << std::endl;
        _framesRendered = 0;
    }
}
