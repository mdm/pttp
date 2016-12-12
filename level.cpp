#include <fstream>
#include <sstream>

#include "level.h"

Level::Level(const std::string& filename)
{
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
