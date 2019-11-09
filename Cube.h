//
// Created by mike on 05.11.2019.
//

#ifndef MIKECRAFT_CUBE_H
#define MIKECRAFT_CUBE_H


#include <glm/vec3.hpp>
#include <vector>

class Cube {
    std::vector<float> vertices, top, bot, left, right, front, back;

public:
    Cube(float x, float y, float z, bool visible)
    {
        bool isVisible = visible;
        back = {
                x+(-0.5f),  y+(-0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                x+(0.5f),   y+(-0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                x+(0.5f),   y+(0.5f),   z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(0.5f),   y+(0.5f),   z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(-0.5f),  y+(0.5f),   z+(-0.5f),  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                x+(-0.5f),  y+(-0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  0.0f,  0.0f
        };
        front = {
                x+(-0.5f),  y+(-0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                x+(0.5f),   y+(-0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                x+(0.5f),   y+(0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(0.5f),   y+(0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(-0.5f),  y+(0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                x+(-0.5f),  y+(-0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  0.0f
        };
        left = {
                x+(-0.5f),  y+(0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                x+(-0.5f),  y+(0.5f),   z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                x+(-0.5f),  y+(-0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(-0.5f),  y+(-0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(-0.5f),  y+(-0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                x+(-0.5f),  y+(0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  0.0f
        };
        right = {
                x+(0.5f),  y+(0.5f),    z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                x+(0.5f),  y+(0.5f),    z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                x+(0.5f),  y+(-0.5f),   z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(0.5f),  y+(-0.5f),   z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(0.5f),  y+(-0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                x+(0.5f),  y+(0.5f),    z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  0.0f
        };
        bot = {
                x+(-0.5f),  y+(-0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                x+(0.5f),   y+(-0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                x+(0.5f),   y+(-0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(0.5f),   y+(-0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(-0.5f),  y+(-0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                x+(-0.5f),  y+(-0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  0.0f,  0.0f
        };
        top = {
                x+(-0.5f),  y+(0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                x+(0.5f),   y+(0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                x+(0.5f),   y+(0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(0.5f),   y+(0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(-0.5f),  y+(0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                x+(-0.5f),  y+(0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  0.0f,  0.0f
        };
    }

    void useBack()
    {
        vertices.insert(vertices.end(), back.begin(), back.end());
    }
    void useRight()
    {
        vertices.insert(vertices.end(), left.begin(), left.end());
    }
    void useLeft()
    {
        vertices.insert(vertices.end(), right.begin(), right.end());
    }
    void useTop()
    {
        vertices.insert(vertices.end(), top.begin(), top.end());
    }
    void useBot()
    {
        vertices.insert(vertices.end(), bot.begin(), bot.end());
    }
    void useFront()
    {
        vertices.insert(vertices.end(), front.begin(), front.end());
    }
    std::vector<float> getVertices()
    {
        return vertices;
    }

};


#endif //MIKECRAFT_CUBE_H
