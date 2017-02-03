#ifndef QUAD_H
#define QUAD_H

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Quad
{
public:
    Quad(int width, int height, int z, uint32_t texture);
    ~Quad();
    
    int getWidth();
    void setWidth(int width);
    int getHeight();
    void setHeight(int height);
    int getZ();
    void setZ(int z);
    uint32_t getTexture();
    void setTexture(uint32_t handle);
    glm::mat4 getTransform();
    void setTransform(const glm::mat4& transform);

    static float vertices[18];
    static float texCoords[12];

private:
    int _width, _height, _z;
    uint32_t _texture;
    glm::mat4 _transform;
};

#endif // QUAD_H
