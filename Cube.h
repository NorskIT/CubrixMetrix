//
// Created by mike on 05.11.2019.
//

#ifndef MIKECRAFT_CUBE_H
#define MIKECRAFT_CUBE_H


#include <glm/vec3.hpp>
#include <vector>
/**
 * Cube represent a single voxel
 */
class Cube {
    std::vector<float> vertices, top, bot, left, right, front, back;

public:
    /**
     * Basic constructor for a single cube/voxel
     * Creates all the vertices for a complete voxel based on param x,y,z.
     * @param x pos
     * @param y pos
     * @param z pos
     * @param visible
     */
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
                x+(0.5f),   y+(0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                x+(0.5f),   y+(0.5f),   z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                x+(0.5f),   y+(-0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(0.5f),   y+(-0.5f),  z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(0.5f),   y+(-0.5f),  z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                x+(0.5f),   y+(0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  0.0f
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
                x+(-0.5f),  y+(0.5f),   z+(-0.5f),  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                x+(0.5f),   y+(0.5f),   z+(-0.5f),  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                x+(0.5f),   y+(0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(0.5f),   y+(0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                x+(-0.5f),  y+(0.5f),   z+(0.5f),   0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                x+(-0.5f),  y+(0.5f),   z+(-0.5f),  0.0f,  0.0f, -1.0f,  0.0f,  0.0f
        };
    }


    /**
     * Adds all vertices associated with Back-side to the main vertice array
     */
    void useBack()
    {
        vertices.insert(vertices.end(), back.begin(), back.end());
    }

    /**
     * Adds all vertices associated with right-side to the main vertice array
     */
    void useRight()
    {
        vertices.insert(vertices.end(), left.begin(), left.end());
    }

    /**
     * Adds all vertices associated with Left-side to the main vertice array
     */
    void useLeft()
    {
        vertices.insert(vertices.end(), right.begin(), right.end());
    }

    /**
     * Adds all vertices associated with Top-side to the main vertice array
     */
    void useTop()
    {
        vertices.insert(vertices.end(), top.begin(), top.end());
    }

    /**
     * Adds all vertices associated with Bot-side to the main vertice array
     */
    void useBot()
    {
        vertices.insert(vertices.end(), bot.begin(), bot.end());
    }

    /**
     * Adds all vertices associated with Front-side to the main vertice array
     */
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
