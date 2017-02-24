#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>

#include "texture.h"
#include "quad.h"

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    enum class ResourceType {unknown, texture, quad};
    ResourceType getResourceType(uint32_t handle);

    uint32_t loadTextureFromPNG(const std::string& filename);
    uint32_t makeCheckerboardTexture(int width, int height, int steps);
    Texture* getTexture(uint32_t handle);

    uint32_t makeQuad(int width, int height, int z, uint32_t texture);
    Quad* getQuad(uint32_t handle);

private:
    uint32_t _nextFreeHandle;

    std::map<uint32_t, Texture*> _textures;
    std::map<uint32_t, Quad*> _quads;
};

#endif // RESOURCE_MANAGER_H
