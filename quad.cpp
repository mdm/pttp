#include <iostream>
#include <SDL_image.h>
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

Quad::Quad(int width, int height, int z)
{
    _handle = 0;
    _z = z;
    setTexture(width, height, makeCheckerBoard(width, height, width / 10));
}

Quad::Quad(const std::string& pngFilename, int z)
{
    _handle = 0;
    _z = z;

    SDL_PixelFormat targetFormat;
    std::memset(&targetFormat, 0, sizeof(targetFormat));
    targetFormat.format = SDL_PIXELFORMAT_RGBA8888;
    targetFormat.BitsPerPixel = 32;
    targetFormat.BytesPerPixel = 4;
    targetFormat.Rmask = 255;
    targetFormat.Gmask = 255 << 8;
    targetFormat.Bmask = 255 << 16;
    targetFormat.Amask = 255 << 24;
    SDL_Surface* originalSurface = IMG_Load(pngFilename.c_str());
    SDL_Surface* convertedSurface = SDL_ConvertSurface(originalSurface, &targetFormat, 0);
    SDL_FreeSurface(originalSurface);

    std::cout << pngFilename << " " << convertedSurface << std::endl;
    std::cout << convertedSurface->w << ", " << convertedSurface->h << std::endl;
    std::cout << (int)convertedSurface->format->BitsPerPixel << std::endl;
    std::cout << (int)convertedSurface->format->BytesPerPixel << std::endl;
    std::cout << convertedSurface->format->Rmask << std::endl;
    std::cout << convertedSurface->format->Gmask << std::endl;
    std::cout << convertedSurface->format->Bmask << std::endl;
    std::cout << convertedSurface->format->Amask << std::endl;
    // TODO: handle ownership
    setTexture(convertedSurface->w, convertedSurface->h, (uint8_t*) convertedSurface->pixels);
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

uint32_t Quad::getHandle()
{
    return _handle;
}

void Quad::setHandle(uint32_t handle)
{
    _handle = handle;
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
                texture[i++] = 128;
            }
        }
    }

    return texture;
}
