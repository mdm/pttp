#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "resource_manager.h"
#include "quad.h"

class Level
{
public:
    Level(const std::string& filename);
    ~Level();

    std::string toString(); // TODO: replace with proper conversion operator
    std::vector<uint32_t> getQuads(ResourceManager& resourceManager);
    //bool move(uint8_t direction);

private:
    void load(const std::string& filename);

    uint8_t _grid[28][31];
    uint32_t _quads[28][31];
    uint32_t _textures[4];
};

#endif // LEVEL_H
