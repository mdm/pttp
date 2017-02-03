#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    uint32_t loadTextureFromPNG(const std::string& filename);
    uint32_t makeCheckerboardTexture(int width, int height, int steps);

    uint8_t* getTextureData(uint32_t handle);
    int getTextureWidth(uint32_t handle);
    int getTextureHeight(uint32_t handle);

private:
    uint32_t _nextFreeHandle;

    std::map<uint32_t, uint8_t*> _textureData;
    std::map<uint32_t, int> _textureWidths;
    std::map<uint32_t, int> _textureHeights;
};

#endif // RESOURCE_MANAGER_H
