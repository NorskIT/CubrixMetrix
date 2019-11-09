//
// Created by mike on 05.11.2019.
//

#ifndef MIKECRAFT_CHUNKMANAGER_H
#define MIKECRAFT_CHUNKMANAGER_H


#include <vector>
#include <iostream>
#include <random>
#include "Cube.h"
#include "glm/gtc/noise.hpp"
#include "dep/SimplexNoise.h"
#include "Chunk.h"


class ChunkManager {

    //Think of a chunk as 4 blocks. These are the names representing these blocks.
    enum GenerateDirection {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

public:

    std::vector<float> world1;
    std::vector<float> world2;

    /*
     * [nw][n][ne]
     * [w ][c][e ]
     * [sw][s][se]
     */

    std::vector<float> nw; //North west
    std::vector<float> ne; //North east
    std::vector<float> sw; //South west
    std::vector<float> se; //North east
    std::vector<float> s; //South
    std::vector<float> e; //East
    std::vector<float> w; //West
    std::vector<float> n; //North
    std::vector<float> c; //Center

    glm::vec2 playerChunkPos; //Which chunk player is in. Example, if he's in the 3rd created chunk, he would be in 0,3.

    long seed;
    long chunkPosX = 0;
    long chunkPosZ = 0;

    int i = 0;

    ChunkManager()
    {
        seed = 1; //rand()%(1000000-0 + 1);
        std::cout << "seed: " << seed << std::endl;
    }

    void CheckWherePlayerPosition(glm::vec3 playerPos)
    {

        /*To find First X and Z of chunk the player stands in, we have to divide
         * the players X and Y coord by 16, so that we know how many chunk out of world
         * center we are, then we multiply by 16, so that we get the exact X and Y coord
         * of 0,0 of current chunk
         */
        int currentPlayerChunkX= (((int)floor(playerPos.x))/16)*16;
        int currentPlayerChunkY= (((int)floor(playerPos.z))/16)*16;

        if(currentPlayerChunkX < playerChunkPos.x)
        {
            generateChunk(playerPos, RIGHT);
            std::cout << "Player move RIGHT to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkY << std::endl;

        }
        if(currentPlayerChunkX > playerChunkPos.x)
        {
            generateChunk(playerPos, LEFT);
            std::cout << "Player move LEFT to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkY << std::endl;
        }
        if(currentPlayerChunkY > playerChunkPos.y)
        {
            generateChunk(playerPos, UP);
            std::cout << "Player move UP to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkY << std::endl;
        }
        if(currentPlayerChunkY < playerChunkPos.y)
        {
            generateChunk(playerPos, DOWN);
            std::cout << "Player move DOWN to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkY << std::endl;
        }
        if(playerChunkPos.x != currentPlayerChunkX || playerChunkPos.y != currentPlayerChunkY)
        {
            std::cout << "" << std::endl;
        }
        playerChunkPos.x = currentPlayerChunkX;
        playerChunkPos.y = currentPlayerChunkY;

    }

    void generateChunk(glm::vec3 playerPos, GenerateDirection direction) {

    }
    void generateChunk(glm::vec3 playerPos)
    {
        GenerateDirection direction = LEFT;

        Chunk chunk = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ), seed);
        std::vector<float> lastNW = nw;
        std::vector<float> lastNE = ne;
        std::vector<float> lastSW = sw;
        std::vector<float> lastSE = se;
        std::vector<float> lastS = s;
        std::vector<float> lastW = w;
        std::vector<float> lastE = e;
        std::vector<float> lastN = n;
        std::vector<float> lastC = c;
        if(direction == LEFT)
        {
            c=w;
            n=nw;
            s=sw;
            ne = n;
            e = c;
            se = s;

            Chunk swChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
            Chunk wChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ), seed);
            Chunk nwChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
            sw.clear();
            sw.insert(sw.end(), swChunk.vertices.begin(), swChunk.vertices.end());
        }
        /*
        if(direction == RIGHT)
        {
            nw = n;
            w = c;
            sw = s;
            Chunk se = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
            Chunk e = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ), seed);
            Chunk ne = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
        }
        if(direction == UP)
        {
            sw = w;
            s = c;
            se = e;
            Chunk nw = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
            Chunk n = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ+CHUNK_WIDTH), seed);
            Chunk ne = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
        }
        if(direction == DOWN)
        {
            nw = w;
            n = c;
            ne = e;
            Chunk sw = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
            Chunk s = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ-CHUNK_WIDTH), seed);
            Chunk se = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
        }*/


        //We add two list, for each vertex array, so that we easily can add different texture on every other chunk.
        if(i%2 == 0)
        {
            world1.insert(world1.end(), chunk.vertices.begin(), chunk.vertices.end());
        } else {
            world2.insert(world2.end(), chunk.vertices.begin(), chunk.vertices.end());
        }

        chunkPosZ += 16;
        if(chunkPosZ%176 == 0)
        {
            chunkPosX += 16;
            chunkPosZ = 0;
        }
        i++;

    }


};


#endif //MIKECRAFT_CHUNKMANAGER_H
