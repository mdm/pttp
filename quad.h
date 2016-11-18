#ifndef QUAD_H
#define QUAD_H

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Quad
{
public:
    Quad(int width, int height, int z);
    Quad(const std::string& pngFilename, int z);
    ~Quad();
    
    int getWidth();
    int getHeight();
    uint8_t* getTexture();
    void setTexture(int width, int height, uint8_t* texture, bool copy = false);
    int getZ();
    void setZ(int z);
    uint32_t getHandle();
    void setHandle(uint32_t handle);
    glm::mat4 getTransform();
    void setTransform(const glm::mat4& transform);

    static float vertices[18];
    static float texCoords[12];
private:
    uint8_t* makeCheckerBoard(int width, int height, int steps);

    int _width, _height, _z;
    uint32_t _handle;
    uint8_t* _texture;
    glm::mat4 _transform;
};

#endif // QUAD_H
