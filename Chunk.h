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

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

//Reduce values on noice. Higher value, less noise(High value == Flat terrain)
#define NOISE_HEIGHT 100
#define NOISE_WIDTH 100

class Chunk {

public:

    float map[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];
    std::vector<float> vertices;
    glm::vec3 pos;
    long currentSeed;

    /* Vec3 is to know where the chunk starts, so that we know where to continue
     * the terrain building/noise. Without this each chunk will look alike, and the
     * corners will be hard.
     *
     * Seed is seed.
     *
     * */

    Chunk(glm::vec3 chunkPos, long seed)
    {
        pos = chunkPos;
        currentSeed = seed;

        //3 for loops, representing X,Y,Z coords.
        for(float x = 0; x < CHUNK_WIDTH; ++x) {
            for (float y = 0; y < CHUNK_HEIGHT; ++y) {
                for (float z = 0; z < CHUNK_WIDTH; ++z) {

                    //Add the difference for each chunk, pluss noise values.
                    float xPos = (x+pos.x);
                    float yPos = (y+pos.y);
                    float zPos = (z+pos.z);


                    float value = GenerateNoisePoint(xPos, yPos, zPos);

                    /*
                     *
                     * Example:
                     * If Y, which is out height, is larger than the value SimplexNoise has returned,
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


    /*
     * Here's where the magic happends. SimplexNoise is a determinant formula and
     * will always calculate the same value based on the input.
     */
    float GenerateNoisePoint(float x, float y, float z)
    {
        float value = SimplexNoise::noise(x/NOISE_WIDTH, y/NOISE_WIDTH, z/NOISE_HEIGHT)*CHUNK_HEIGHT;
        if(value < 0) {
            value *= -1;
        }
        return value;
    }

    void bindChunkIntoVertices()
    {
        float xPos, yPos, zPos;
        std::vector<float> vertices_holder;
        for(int x = 0; x < CHUNK_WIDTH; ++x) {
            for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                for (int z = 0; z < CHUNK_WIDTH; ++z) {

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

                    //Renders bottom of chunk.
                    if(y == 0)
                    {
                        //cube.useBot();
                    }



                    if(y > 0)
                    {
                        if(map[x][y-1][z] != 1) cube.useBot();
                    }
                    if(y < CHUNK_HEIGHT - 1)
                    {
                        if(map[x][y+1][z] != 1) cube.useTop();
                    }
                    if(x > 0)
                    {
                        if(map[x-1][y][z] != 1) cube.useRight();
                    }
                    if(x < CHUNK_WIDTH - 1)
                    {
                        if(map[x+1][y][z] != 1) cube.useLeft();
                    }
                    if(z > 0)
                    {
                        if(map[x][y][z-1] != 1) cube.useBack();
                    }
                    if(z < CHUNK_WIDTH - 1)
                    {
                        if(map[x][y][z+1] != 1) cube.useFront();
                    }

                    /*
                     * We then need to check if block hits anything outside of current chunk.
                     */
                    if(z == 0)
                    {
                        float zDiff = z+pos.z-1;
                        float value = GenerateNoisePoint((x+pos.x),(y+pos.y),(zDiff));
                        if(value < y)
                        {
                            cube.useBack();
                        }
                    }
                    if(z == CHUNK_WIDTH-1)
                    {
                        float zDiff = z+pos.z+1;
                        float value = GenerateNoisePoint((x+pos.x),(y+pos.y),(zDiff));
                        if(value < y)
                        {
                            cube.useFront();
                        }
                    }

                    if(x == 0)
                    {
                        float xDiff = x+pos.x-1;
                        float value = GenerateNoisePoint((xDiff),(y+pos.y),(z+pos.z));
                        if(value < y)
                        {
                            cube.useRight();
                        }
                    }
                    if(x == CHUNK_WIDTH-1)
                    {
                        float xDiff = x+pos.x+1;
                        float value = GenerateNoisePoint((xDiff),(y+pos.y),(z+pos.z));
                        if(value < y)
                        {
                            cube.useLeft();
                        }
                    }



                    vertices_holder = cube.getVertices();
                    vertices.insert(vertices.end(), vertices_holder.begin(), vertices_holder.end());
                    vertices_holder.clear();
                }
            }
        }
    }

};


#endif //MIKECRAFT_CHUNK_H
