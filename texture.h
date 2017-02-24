#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
    Texture(int width, int height, uint8_t* data, const std::string& hash);
    ~Texture();

    int getWidth();
    int getHeight();
    uint8_t* getData();
    std::string getHash();
private:
    int _width;
    int _height;
    uint8_t* _data;
    std::string _hash;
};

#endif // TEXTURE_H

