#include <cstring>
#include <SDL_image.h>

#include "resource_manager.h"

ResourceManager::ResourceManager() : _nextFreeHandle(1)
{
}

ResourceManager::~ResourceManager()
{
    for(auto texture : _textures)
    {
        delete texture.second;
    }

    for(auto quad : _quads)
    {
        delete quad.second;
    }
}

ResourceManager::ResourceType ResourceManager::getResourceType(uint32_t handle)
{
    if(_textures.find(handle) != _textures.end())
    {
        return ResourceType::texture;
    }

    if(_quads.find(handle) != _quads.end())
    {
        return ResourceType::quad;
    }

    return ResourceType::unknown;
}

uint32_t ResourceManager::loadTextureFromPNG(const std::string& filename)
{
    uint32_t handle = _nextFreeHandle++;

    SDL_PixelFormat targetFormat;
    std::memset(&targetFormat, 0, sizeof(targetFormat));
    targetFormat.format = SDL_PIXELFORMAT_RGBA8888;
    targetFormat.BitsPerPixel = 32;
    targetFormat.BytesPerPixel = 4;
    targetFormat.Rmask = 255;
    targetFormat.Gmask = 255 << 8;
    targetFormat.Bmask = 255 << 16;
    targetFormat.Amask = 255 << 24;

    SDL_Surface* originalSurface = IMG_Load(filename.c_str());
    SDL_Surface* convertedSurface = SDL_ConvertSurface(originalSurface, &targetFormat, 0);
    SDL_FreeSurface(originalSurface);

    int size = convertedSurface->w * convertedSurface->h * 4;
    uint8_t* texture = new uint8_t[size];
    std::memcpy(texture, convertedSurface->pixels, size);
    SDL_FreeSurface(convertedSurface);

    std::string hash = "checkerboard: "; // TODO: add parameters to hash
    _textures[handle] = new Texture(convertedSurface->w, convertedSurface->h, texture, hash);
    return handle;
}

uint32_t ResourceManager::makeCheckerboardTexture(int width, int height, int steps)
{
    // TODO: allow custom colors
    uint32_t handle = _nextFreeHandle++;

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

    std::string hash = "checkerboard: "; // TODO: add parameters to hash
    _textures[handle] = new Texture(width, height, texture, hash);
    return handle;
}

Texture* ResourceManager::getTexture(uint32_t handle)
{
    return _textures.at(handle);
}

uint32_t ResourceManager::makeQuad(int width, int height, int z, uint32_t texture)
{
    uint32_t handle = _nextFreeHandle++;
    
    _quads[handle] = new Quad(width, height, z, texture);
    return handle;
}

Quad* ResourceManager::getQuad(uint32_t handle)
{
    return _quads.at(handle);
}

