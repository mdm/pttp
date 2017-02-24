#include "texture.h"

Texture::Texture(int width, int height, uint8_t* data, const std::string& hash) : _width(width), _height(height), _data(data), _hash(hash)
{
}

Texture::~Texture()
{
    delete _data;
}

int Texture::getWidth()
{
    return _width;
}

int Texture::getHeight()
{
    return _height;
}

uint8_t* Texture::getData()
{
    return _data;
}

std::string Texture::getHash()
{
    return _hash;
}
