#include "quad.h"

float Quad::vertices[] = {
    -1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f
};

float Quad::texCoords[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

Quad::Quad(int width, int height, int z, uint32_t texture)
{
    _width = width;
    _height =  height;
    _z = z;
    _texture = texture;
}

Quad::~Quad()
{
}

int Quad::getWidth()
{
    return _width;
}

void Quad::setWidth(int width)
{
    _width = width;
}

int Quad::getHeight()
{
    return _height;
}

void Quad::setHeight(int height)
{
    _height =  height;
}

int Quad::getZ()
{
    return _z;
}

void Quad::setZ(int z)
{
    _z = z;
}

uint32_t Quad::getTexture()
{
    return _texture;
}

void Quad::setTexture(uint32_t texture)
{
    _texture = texture;
}

glm::mat4 Quad::getTransform()
{
    glm::mat4 translate = glm::translate(glm::vec3(_width / 2.0f, _height / 2.0f, (float) -_z));
    glm::mat4 scale = glm::scale(glm::vec3(_width / 2.0f, _height / 2.0f, 1.0f));
    return translate * _transform * scale;
}

void Quad::setTransform(const glm::mat4& transform)
{
    _transform = transform;
}

