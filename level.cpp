#include <fstream>
#include <sstream>

#include "level.h"

//Level::Level(ResourceManager& resourceManager, const std::string& filename) : _resourceManager(resourceManager)
Level::Level(const std::string& filename)
{
    for(int i = 0; i < 4; i++) {
        _textures[i] = 0;
    }

    for(int y = 0; y < 31; ++y)
    {
        for(int x = 0; x < 28; ++x)
        {
            _quads[x][y] = 0;
        }
    }

    load(filename);
}


Level::~Level()
{
}


std::string Level::toString()
{
    std::string level;
    for(int y = 0; y < 31; ++y)
    {
        for(int x = 0; x < 28; ++x)
        {
            switch(_grid[x][y]) // TODO: use enums?
            {
                case 0: // wall
                    level += "# ";
                    break;
                case 1: // painted street
                    level += "  ";
                    break;
                case 2: // unpainted street
                    level += ". ";
                    break;
                case 3: // power up
                    level += "* ";
                    break;
                default:
                    break;
            }
        }
        level += "\n";
    }
    return level;
}


void Level::load(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    int y = 0;
    while(std::getline(file, line))
    {
        std::stringstream tokens(line);
        std::string token;
        int x = 0;
        while(tokens >> token)
        {
            _grid[x][y] = 0;
            if(token == "#")
            {
                _grid[x][y] = 2;
            }
            ++x;
        }
        ++y;
    }
}

std::vector<uint32_t> Level::getQuads(ResourceManager& resourceManager) {
    const int tileSize = 10;

    if(_textures[0] == 0) {
        _textures[0] = resourceManager.makeRectangleTexture(tileSize, tileSize, 0, 0, 255, 255);
    }
    if(_textures[1] == 0) {
        _textures[1] = resourceManager.makeRectangleTexture(tileSize, tileSize, 0, 0, 0, 255);
    }
    if(_textures[2] == 0) {
        _textures[2] = resourceManager.makeEllipseTexture(tileSize, tileSize, 255, 255, 255, 255);
    }
    if(_textures[3] == 0) {
        _textures[3] = resourceManager.makeEllipseTexture(tileSize, tileSize, 255, 0, 0, 255);
    }

    std::vector<uint32_t> quads;

    for(int y = 0; y < 31; ++y)
    {
        for(int x = 0; x < 28; ++x)
        {
            if(_quads[x][y] == 0) {
                _quads[x][y] = resourceManager.makeQuad(tileSize, tileSize, 20, _textures[_grid[x][y]]);
                resourceManager.getQuad(_quads[x][y])->setTransform(glm::translate(glm::vec3(x * tileSize, y * tileSize, 0.0f)));
            } else {
                resourceManager.getQuad(_quads[x][y])->setTextureHandle(_textures[_grid[x][y]]);
            }
            quads.push_back(_quads[x][y]);
        }
    }

    return quads;
}