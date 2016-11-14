#include <iostream>
#include "quad.h"

float Quad::vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
};

float Quad::texCoords[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

Quad::Quad(int width, int height, int z)
{
    _z = z;
    setTexture(width, height, makeCheckerBoard(width, height, 10));
}

Quad::Quad(const std::string& pngFilename, int z)
{
}

Quad::~Quad()
{
    delete _texture;
}

int Quad::getWidth()
{
    return _width;
}

int Quad::getHeight()
{
    return _height;
}

uint8_t* Quad::getTexture()
{
    return _texture;
}

void Quad::setTexture(int width, int height, uint8_t* texture, bool copy)
{
    _width = width;
    _height =  height;
    if(copy)
    {
        //TODO make a copy
    }
    else
    {
        _texture = texture;
    }
}

int Quad::getZ()
{
    return _z;
}

void Quad::setZ(int z)
{
    _z = z;
}

glm::mat4 Quad::getTransform()
{
    glm::mat4 translateZ = glm::translate(glm::vec3(0.0f, 0.0f, (float)_z));
    glm::mat4 scale = glm::scale(glm::vec3((float)_width, (float)_height, 1.0f));
    return translateZ * _transform * scale;
}

void Quad::setTransform(const glm::mat4& transform)
{
    _transform = transform;
}

uint8_t* Quad::makeCheckerBoard(int width, int height, int steps)
{
    uint8_t* texture = new uint8_t[width * height * 4];

    int i = 0;
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            if((x / (width / steps)) % 2 == (y / (height / steps)) % 2)
            {
                texture[i++] = 0;
                texture[i++] = 0;
                texture[i++] = 255;
                texture[i++] = 255;
            }
            else
            {
                texture[i++] = 0;
                texture[i++] = 0;
                texture[i++] = 0;
                texture[i++] = 0;
            }
        }
    }

    return texture;
}
