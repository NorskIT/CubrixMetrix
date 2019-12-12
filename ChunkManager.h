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

    std::vector<float> world; //Cache
    std::vector<float> water; //Cache



    //A bool which is used to check if user has moved out of pre-generated chunks
    bool hasPlayerMoved = false;

    long seed;

    ChunkManager() = default;
    ChunkManager(glm::vec3 playerPos)
    {
        startupGenerateChunk(playerPos);
        seed = rand()%(1000000-0 + 1);
        std::cout << "seed: " << seed << std::endl;
    }

    void checkPlayerPosition(glm::vec3 playerPos)
    {

        /* To find First X and Z of chunk the player stands in, we have to divide
         * the players X and Y coord by 16, so that we know how many chunk out of world
         * center we are, then we multiply by 16, so that we get the exact X and Y coord
         * of 0,0 of current chunk
         */
        int currentPlayerChunkX = (int)((floor(playerPos.x)) / CHUNK_WIDTH) * CHUNK_WIDTH;
        int currentPlayerChunkZ = (int)((floor(playerPos.z)) / CHUNK_WIDTH) * CHUNK_WIDTH;
        if(playerPos.x < 0) {
            currentPlayerChunkX -= CHUNK_WIDTH;
        }if(playerPos.z < 0) {
            currentPlayerChunkZ -= CHUNK_WIDTH;
        }


        if(currentPlayerChunkX < playerChunkPos.x)
        {
            generateChunk(RIGHT, currentPlayerChunkX, currentPlayerChunkZ);
            //std::cout << "Player move RIGHT to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkZ << std::endl;
        }
        if(currentPlayerChunkX > playerChunkPos.x)
        {
            generateChunk(LEFT, currentPlayerChunkX, currentPlayerChunkZ);
            //std::cout << "Player move LEFT to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkZ << std::endl;
        }
        if(currentPlayerChunkZ > playerChunkPos.y)
        {
            generateChunk(UP, currentPlayerChunkX, currentPlayerChunkZ);
            //std::cout << "Player move UP to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkZ << std::endl;
        }
        if(currentPlayerChunkZ < playerChunkPos.y)
        {
            generateChunk(DOWN, currentPlayerChunkX, currentPlayerChunkZ);
            //std::cout << "Player move DOWN to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkZ << std::endl;
        }
        if(playerChunkPos.x != currentPlayerChunkX || playerChunkPos.y != currentPlayerChunkZ)
        {
            //std::cout << "Player has move into a different chunk" << std::endl;
            //std::cout << "World size: " << world.size() << std::endl;
            std::cout << "Water size: " << water.size() << std::endl;
        }
        playerChunkPos.x = currentPlayerChunkX;
        playerChunkPos.y = currentPlayerChunkZ;

    }

    /*
     * We use this only 1 time. This is for generating all the
     * terrain around the player, when the player enters the world.
     */
    void startupGenerateChunk(glm::vec3 playerPosDirection) {

        int chunkPosX = (((int)floor(playerPosDirection.x))/CHUNK_WIDTH)*CHUNK_WIDTH;
        int chunkPosZ = (((int)floor(playerPosDirection.z))/CHUNK_WIDTH)*CHUNK_WIDTH;
        InsertIntoCache(createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed));
        InsertIntoCache(createChunk(glm::vec3(chunkPosX, 0, chunkPosZ+CHUNK_WIDTH), seed));
        InsertIntoCache(createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed));
        InsertIntoCache(createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ), seed));
        InsertIntoCache(createChunk(glm::vec3(chunkPosX, 0, chunkPosZ), seed));
        InsertIntoCache(createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ), seed));
        InsertIntoCache(createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed));
        InsertIntoCache(createChunk(glm::vec3(chunkPosX, 0, chunkPosZ-CHUNK_WIDTH), seed));
        InsertIntoCache(createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed));
    }

    bool CheckIfInCache(int x, int z) {
        for(auto & cachedChunk : cachedChunks)
        {
            if(cachedChunk.equals(x, z))
            {
                return true;
            }
        }
        return false;
    }

    void generateChunk(GenerateDirection direction, int chunkPosX, int chunkPosZ)
        {
            Chunk chunks[3];
            if(direction == RIGHT)
            {
                // if LEFT, generate SW, W, NW
                InsertIntoCache(createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed)); // SW
                InsertIntoCache(createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ), seed)); //W
                InsertIntoCache(createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed)); // NW
                return;
            }

            if(direction == LEFT)
            {
                // if RIGHT, generate SE, E, NE
                InsertIntoCache(createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed)); // SE
                InsertIntoCache(createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ), seed)); // E
                InsertIntoCache(createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed)); // NE
                return;
            }
            if(direction == UP)
            {
                // if up, generate NW, N, NE
                InsertIntoCache(createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed)); // NW
                InsertIntoCache(createChunk(glm::vec3(chunkPosX, 0, chunkPosZ+CHUNK_WIDTH), seed)); // N
                InsertIntoCache(createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed)); // NE
                return;
            }
            if(direction == DOWN)
            {
                // if down, generate SW, S, SE
                InsertIntoCache(createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed)); // SW
                InsertIntoCache(createChunk(glm::vec3(chunkPosX, 0, chunkPosZ-CHUNK_WIDTH), seed)); // S
                InsertIntoCache(createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed)); // SE
                return;
            }

    }

    /*
     * This methods will first check if the chunk we want to create exists within the cache.
     * if it does, then we will return that chunk. If not, we return a new chunk.
     */
    Chunk createChunk(glm::vec3 pos, long seed)
    {

        for(auto & cachedChunk : cachedChunks)
        {
            if(cachedChunk.equals(pos.x, pos.z))
            {
                return cachedChunk;
            }
        }

        //If no chunk was found in cache, then players has not moved outside of generated map
        hasPlayerMoved = true;
        return Chunk(glm::vec3(pos.x, pos.y, pos.z), seed);;
    }

    void InsertIntoCache(Chunk chunk)
    {
        bool chunkHasWater = false;
        Chunk waterChunk;
        for(auto & cachedWaterChunk : cachedWaterChunks)
        {
            if(cachedWaterChunk.equals(chunk.pos.x, chunk.pos.z))
            {
                chunkHasWater = true;
                waterChunk = cachedWaterChunk;
            }
        }
        //If chunk does not exists in cache, then append chunk to cache.
        if(!chunkHasWater)
        {
            waterChunk = Chunk(chunk, 3);
        }

        cachedWaterChunks.insert(cachedWaterChunks.end(), waterChunk);
        cachedChunks.insert(cachedChunks.end(), chunk);


        water.insert(water.end(), waterChunk.vertices.begin(), waterChunk.vertices.end());
        world.insert(world.end(), chunk.vertices.begin(), chunk.vertices.end());
        while(world.size() > 8000000)
        {
            world.erase(world.begin(), world.begin()+cachedChunks[0].vertices.size());
            cachedChunks.erase(cachedChunks.begin());
            water.erase(water.begin(), water.begin()+cachedWaterChunks[0].vertices.size());
            cachedWaterChunks.erase(cachedWaterChunks.begin());
        }


    }
    private:
        int waterToDelete = 0;
        std::vector<Chunk> cachedChunks;
        std::vector<Chunk> cachedWaterChunks;
        glm::vec2 playerChunkPos; //Which chunk player is in. Example, if he's in the 3rd created chunk, he would be in 0,3.
};


#endif //MIKECRAFT_CHUNKMANAGER_H
