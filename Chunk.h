//
// Created by mike on 06.11.2019.
//

#ifndef MIKECRAFT_CHUNK_H
#define MIKECRAFT_CHUNK_H

#include <vector>
#include <iostream>
#include <random>
#include "Cube.h"
#include "glm/gtc/noise.hpp"
#include "dep/SimplexNoise.h"


/*
 * MAX WIDTH:
 *      Width 182
 *      Height 7
 * MAX HEIGHT
 *      Width 7
 *      Height 2500+ <- It just lags at this altitude.

 */
#define CHUNK_WIDTH 120
#define CHUNK_HEIGHT 13

//Reduce values on noise. Higher value equals less noise(High value == Flat terrain)
#define NOISE_HEIGHT 40
#define NOISE_WIDTH_X 60
#define NOISE_WIDTH_Z 60

#define WATER_HEIGHT 5

/**
 * Chunk is a collection of X amount of cubes.
 */
class Chunk {

public:

    float map[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];
    std::vector<float> vertices;
    std::vector<float> water;
    bool isWater = false;
    glm::vec3 pos;
    long currentSeed;

    /* Vec3 is to know where the chunk starts, so that we know where to continue
     * the terrain building/noise. Without this each chunk will look alike, and the
     * corners will be hard.
     *
     * Seed is seed.
     *
     * */

    Chunk() = default;


    /**
     * Constructor for normal chunk.
     * @param chunkPos
     * @param seed
     */
    Chunk(glm::vec3 chunkPos, long seed)
    {
        pos = chunkPos;
        currentSeed = seed;

        //3 for loops, representing X,Y,Z coords.
        for(float x = 0; x < CHUNK_WIDTH; ++x) {
            for (float y = 0; y < CHUNK_HEIGHT; ++y) {
                for (float z = 0; z < CHUNK_WIDTH; ++z) {

                    //Add the difference for each chunk, plus noise values.
                    float xPos = (x+pos.x);
                    float yPos = (y+pos.y);
                    float zPos = (z+pos.z);


                    float value = GenerateNoisePoint(xPos, yPos, zPos);

                    /*
                     *
                     * Example:
                     * If Y, which is our height, is larger than the value SimplexNoise has returned,
                     * based on X, Y and Z, then we will NOT draw that cube.
                     *
                     * This way, we can always calulcate our way back to every block, which comes
                     * in handy later when we need to know which side of the cube to draw.
                     */


                    if(value > y)
                    {
                        map[(int)x][(int)y][(int)z] = 1;
                    } else {
                        map[(int)x][(int)y][(int)z] = 0;
                    }
                }
            }
        }
        //After map is created, we need to determine which side/vertices to draw
        bindChunkIntoVertices();
    }

    /**
     * Water chunks works similar to normal chunk. Except its negative. That means that it'll fill
     * all blocks that are suppouse to be invisible.
     * It also will not add cubes above waterheight
     * @param chunk , the chunk which we add water too
     * @param waterheight , height limit of generated cubes
     */
    Chunk(Chunk chunk, int waterheight)
    {
        isWater = true;
        pos = chunk.pos;

        //3 for loops, representing X,Y,Z coords.
        for(float x = 0; x < CHUNK_WIDTH; ++x) {
            for (float y = 0; y < WATER_HEIGHT; ++y) {
                for (float z = 0; z < CHUNK_WIDTH; ++z) {

                    //Add the difference for each chunk, plus noise values.
                    float xPos = (x+pos.x);
                    float yPos = (y+pos.y);
                    float zPos = (z+pos.z);


                    float value = GenerateNoisePoint(xPos, yPos, zPos);


                    if(value < y)
                    {
                        map[(int)x][(int)y][(int)z] = 1;
                    } else {
                        map[(int)x][(int)y][(int)z] = 0;
                    }
                }
            }
        }
        //After map is created, we need to determine which side/vertices to draw
        bindChunkIntoVertices();
    }

    /**
     * Uses Perlin noise/ Simplex noise to procedurally generate predictable noise
     * @param x , x position in current chunk
     * @param y , y position in current chunk
     * @param z , z position in current chunk
     * @return noise value
     */
    float GenerateNoisePoint(float x, float y, float z)
    {
        //We divide it by set values, to dynamically edit the values more to our likings.
        SimplexNoise noise = SimplexNoise(x/NOISE_WIDTH_X, y/NOISE_HEIGHT, z / NOISE_WIDTH_Z);
        float value = noise.noise(x/NOISE_WIDTH_X, y / NOISE_HEIGHT, z / NOISE_WIDTH_Z) * (CHUNK_HEIGHT - 1) + 1;
        //If value is negative, make it positiv.
        if(value < 0) {
            value *= -1;
        }
        return value;
    }

    /**
     * Method for filtering out which side of a cube to draw.
     * Proceeds to check each side of each cube, and only draw that
     * cube which has an invisible cube in said direction
     */
    void bindChunkIntoVertices()
    {
        //Contains vertices for current cube.
        std::vector<float> vertices_holder;
        for(int x = 0; x < CHUNK_WIDTH; ++x) {
            for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                for (int z = 0; z < CHUNK_WIDTH; ++z) {

                    //Empty previous cubes vertices
                    vertices_holder.clear();

                    //If current chunk is water chunk, do not proceed after set water height.
                    if(isWater && y >= WATER_HEIGHT) continue;

                    //Current cube equals 0(Not-visible), then no need to go any further.
                    if(map[x][y][z] == 0) continue;


                    //Create a new cube, based on X and Z position of chunk.
                    Cube cube = Cube(x+pos.x, y, z+pos.z, true);
                    float value = GenerateNoisePoint((x+pos.x),(y+pos.y),(z+pos.z));

                    //If block is at top of chunk, then top is visible
                    if(y == CHUNK_HEIGHT-1)
                    {
                        cube.useTop();
                    }
                    //If cube is above 0
                    if(y > 0)
                    {
                        //Check if there is a cube below this cube. if no cube, draw vertices for bot
                        if(map[x][y-1][z] != 1) cube.useBot();
                    }
                    //If cube is below set height
                    if(y < CHUNK_HEIGHT - 1)
                    {
                        //Check if there is a cube above this cube. if no cube, draw vertices for top
                        if(map[x][y+1][z] != 1) cube.useTop();
                    }
                    //if cube is within width
                    if(x > 0)
                    {
                        //Check if there is a cube on the right side of this cube. if no cube, draw vertices for right side
                        if(map[x-1][y][z] != 1) cube.useRight();
                    }
                    //if cube is within width
                    if(x < CHUNK_WIDTH - 1)
                    {
                        //Check if there is a cube on the left side of this cube. if no cube, draw vertices for left side
                        if(map[x+1][y][z] != 1) cube.useLeft();
                    }
                    //if cube is within width
                    if(z > 0)
                    {
                        //Check if there is a cube on the back side of this cube. if no cube, draw vertices for back side
                        if(map[x][y][z-1] != 1) cube.useBack();
                    }
                    //if cube is within width
                    if(z < CHUNK_WIDTH - 1)
                    {
                        //Check if there is a cube on the front side of this cube. if no cube, draw vertices for front side
                        if(map[x][y][z+1] != 1) cube.useFront();
                    }

                    /*
                     * We have now checked all sides WITHIN the chunk.
                     * Now we need to check the outside walls of the chunk.
                     * These sides collides with other chunks.
                     * We check this by generating the noise value of each side, to check if there is a
                     * cube or not.
                     */
                    //if cube is at outer back side
                    if(z == 0)
                    {
                        float zDiff = z+pos.z-1;
                        float value = GenerateNoisePoint((x+pos.x),(y+pos.y),(zDiff));
                        if(value < y)
                        {
                            cube.useBack();
                        }
                    }
                    //if cube is at outer front side
                    if(z == CHUNK_WIDTH-1)
                    {
                        float zDiff = z+pos.z+1;
                        float value = GenerateNoisePoint((x+pos.x),(y+pos.y),(zDiff));
                        if(value < y)
                        {
                            cube.useFront();
                        }
                    }
                    //if cube is at outer right side
                    if(x == 0)
                    {
                        float xDiff = x+pos.x-1;
                        float value = GenerateNoisePoint((xDiff),(y+pos.y),(z+pos.z));
                        if(value < y)
                        {
                            cube.useRight();
                        }
                    }
                    //if cube is at outer left side
                    if(x == CHUNK_WIDTH-1)
                    {
                        float xDiff = x+pos.x+1;
                        float value = GenerateNoisePoint((xDiff),(y+pos.y),(z+pos.z));
                        if(value < y)
                        {
                            cube.useLeft();
                        }
                    }
                    //Sets the vertices to placeholder
                    vertices_holder = cube.getVertices();
                    //Adds the vertices to the chunks main vertices holder.
                    vertices.insert(vertices.end(), vertices_holder.begin(), vertices_holder.end());
                }
            }
        }
    }

    /**
     * Checks if this chunk is equal to param chunk
     * @param chunk , chunk to check if equal to this
     * @return true if equal
     */
    bool equals(Chunk chunk)
    {
        return pos.z == chunk.pos.z && pos.x == chunk.pos.x;
    }
    /**
     * Checks if this chunk is equal to start position created by param X and Z
     * @param x coord
     * @param z coord
     * @return true if start pos it equal to this start pos
     */
    bool equals(int x, int z)
    {
        return pos.z == z && pos.x == x;
    }

};


#endif //MIKECRAFT_CHUNK_H
