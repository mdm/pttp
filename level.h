#ifndef LEVEL_H
#define LEVEL_H

class Level
{
public:
    Level(const std::string& filename);
    ~Level();

    std::string toString(); // TODO: replace with proper conversion operator
    //bool move(uint8_t direction);

private:
    void load(const std::string& filename);

    uint8_t _grid[28][31];
};

#endif // LEVEL_H
