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
#include <math.h>

/**
 * The Chunk manager manages all the chunks generated
 */
class ChunkManager {

    //Think of a chunk as flat quad with 4 sides. These are the names representing the sides.
    enum GenerateDirection {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };


public:
    //Main list containing all vertices for terrain
    std::vector<float> world;
    //Main list containing al vertices for water
    std::vector<float> water;

    //A bool which is used to check if user has moved out of pre-generated chunks
    bool hasPlayerMoved = false;

    long seed;

    ChunkManager() = default;
    ChunkManager(glm::vec3 playerPos)
    {
        startupGenerateChunk(playerPos);
        //Generate a random seed, so that we wont have to end up with same terrain generation every time.
        seed = rand()%(1000000-0 + 1);
        std::cout << "seed: " << seed << std::endl;
    }

    /**
     * Checks the players position and starts the process of generating new chunk
     * if the player has moved outside of the chunk the player was in.
     * @param playerPos , players current position
     */
    void checkPlayerPosition(glm::vec3 playerPos)
    {

        /* To find First X and Z of chunk the player stands in, we have to divide
         * the players X and Y coord by CHUNK_WIDTH, so that we know how many chunk out of world
         * center we are, then we multiply by CHUNK_WIDTH, so that we get the exact X and Y coord
         * of 0,0(Start position) of that chunk the player is in
         */
        int currentPlayerChunkX = (int)((floor(playerPos.x)) / CHUNK_WIDTH) * CHUNK_WIDTH;
        int currentPlayerChunkZ = (int)((floor(playerPos.z)) / CHUNK_WIDTH) * CHUNK_WIDTH;
        if(playerPos.x < 0) {
            currentPlayerChunkX -= CHUNK_WIDTH;
        }if(playerPos.z < 0) {
            currentPlayerChunkZ -= CHUNK_WIDTH;
        }

        //If player has moved outside of currents chunk RIGHT side, generate new chunk on RIGHT side.
        if(currentPlayerChunkX < playerChunkPos.x)
        {
            generateChunk(RIGHT, currentPlayerChunkX, currentPlayerChunkZ);
        }

        //If player has moved outside of currents chunk LEFT side, generate new chunk on LEFT side.
        if(currentPlayerChunkX > playerChunkPos.x)
        {
            generateChunk(LEFT, currentPlayerChunkX, currentPlayerChunkZ);
        }

        //If player has moved outside of currents chunk FORWARD side, generate new chunk on FORWARD side.
        if(currentPlayerChunkZ > playerChunkPos.y)
        {
            generateChunk(FORWARD, currentPlayerChunkX, currentPlayerChunkZ);
        }

        //If player has moved outside of currents chunk BACKWARD side, generate new chunk on BACKWARD side.
        if(currentPlayerChunkZ < playerChunkPos.y)
        {
            generateChunk(BACKWARD, currentPlayerChunkX, currentPlayerChunkZ);
        }
        //Sets the players chunk pos to current player chunk pos.
        playerChunkPos.x = currentPlayerChunkX;
        playerChunkPos.y = currentPlayerChunkZ;

    }

    /*
     * Startup function, to generate all chunks around the player at startup
     */
    void startupGenerateChunk(glm::vec3 playerPosDirection) {

        int chunkPosX = (((int)floor(playerPosDirection.x))/CHUNK_WIDTH)*CHUNK_WIDTH;
        int chunkPosZ = (((int)floor(playerPosDirection.z))/CHUNK_WIDTH)*CHUNK_WIDTH;

        //Create new chunk, try to add that chunk into chache.
        TryAppendToCache(createChunk(glm::vec3(chunkPosX + CHUNK_WIDTH, 0, chunkPosZ + CHUNK_WIDTH)));
        TryAppendToCache(createChunk(glm::vec3(chunkPosX - CHUNK_WIDTH, 0, chunkPosZ - CHUNK_WIDTH)));
        TryAppendToCache(createChunk(glm::vec3(chunkPosX + CHUNK_WIDTH, 0, chunkPosZ - CHUNK_WIDTH)));
        TryAppendToCache(createChunk(glm::vec3(chunkPosX - CHUNK_WIDTH, 0, chunkPosZ)));
        TryAppendToCache(createChunk(glm::vec3(chunkPosX + CHUNK_WIDTH, 0, chunkPosZ)));
        TryAppendToCache(createChunk(glm::vec3(chunkPosX, 0, chunkPosZ - CHUNK_WIDTH)));
        TryAppendToCache(createChunk(glm::vec3(chunkPosX, 0, chunkPosZ + CHUNK_WIDTH)));
        TryAppendToCache(createChunk(glm::vec3(chunkPosX, 0, chunkPosZ)));
    }
    
    /**
     * Generates THREE new chunks in said direction.
     *
     * @param direction , direction to generate
     * @param chunkPosX , players current chunk pos X
     * @param chunkPosZ , players current chunk pos Z
     */
    void generateChunk(GenerateDirection direction, int chunkPosX, int chunkPosZ)
        {
            Chunk chunks[3];

            /*
             * Consider the chunk area as following:
             *
             *      [NW]  [N ]  [NE]
             *      [W ]  [C ]  [E ]
             *      [SW ] [S ]  [SE]
             *
             * C is center, and is the current chunk of where the player is.
             * If player moves outside of center, we will generate new chunk on that side the player moved outside.
             *
             * So, if player move from C to W, we will generate new chunk in direction LEFT.
             */

            // if LEFT, generate SW, W, NW
            if(direction == RIGHT)
            {
                TryAppendToCache(createChunk(glm::vec3(chunkPosX - CHUNK_WIDTH, 0, chunkPosZ - CHUNK_WIDTH))); // SW
                TryAppendToCache(createChunk(glm::vec3(chunkPosX - CHUNK_WIDTH, 0, chunkPosZ + CHUNK_WIDTH))); // NW
                TryAppendToCache(createChunk(glm::vec3(chunkPosX - CHUNK_WIDTH, 0, chunkPosZ))); //W
                return;
            }
            // if RIGHT, generate SE, E, NE
            if(direction == LEFT)
            {
                TryAppendToCache(createChunk(glm::vec3(chunkPosX + CHUNK_WIDTH, 0, chunkPosZ - CHUNK_WIDTH))); // SE
                TryAppendToCache(createChunk(glm::vec3(chunkPosX + CHUNK_WIDTH, 0, chunkPosZ + CHUNK_WIDTH))); // NE
                TryAppendToCache(createChunk(glm::vec3(chunkPosX + CHUNK_WIDTH, 0, chunkPosZ))); // E
                return;
            }
            // if up, generate NW, N, NE
            if(direction == FORWARD)
            {
                TryAppendToCache(createChunk(glm::vec3(chunkPosX - CHUNK_WIDTH, 0, chunkPosZ + CHUNK_WIDTH))); // NW
                TryAppendToCache(createChunk(glm::vec3(chunkPosX + CHUNK_WIDTH, 0, chunkPosZ + CHUNK_WIDTH))); // NE
                TryAppendToCache(createChunk(glm::vec3(chunkPosX, 0, chunkPosZ + CHUNK_WIDTH))); // N
                return;
            }
            // if down, generate SW, S, SE
            if(direction == BACKWARD)
            {
                TryAppendToCache(createChunk(glm::vec3(chunkPosX - CHUNK_WIDTH, 0, chunkPosZ - CHUNK_WIDTH))); // SW
                TryAppendToCache(createChunk(glm::vec3(chunkPosX + CHUNK_WIDTH, 0, chunkPosZ - CHUNK_WIDTH))); // SE
                TryAppendToCache(createChunk(glm::vec3(chunkPosX, 0, chunkPosZ - CHUNK_WIDTH))); // S
                return;
            }

    }

    /**
     * Check first if the chunk we want to create exists within the cache.
     * if it does, return cached chunk. If not, return new chunk.
     * @param pos , chunk start position
     * @return correct chunk
     */
    Chunk createChunk(glm::vec3 pos)
    {

        for(auto & cachedChunk : cachedChunks)
        {
            if(cachedChunk.equals(pos.x, pos.z))
            {
                return cachedChunk;
            }
        }

        //If no chunk was found in cache, then players has moved outside of pre-generated map
        hasPlayerMoved = true;
        return Chunk(glm::vec3(pos.x, pos.y, pos.z), seed);;
    }
    /**
     * Adds @chunk to a cache.
     * Also creates water chunk for chunks that has no water.
     * @param chunk , chunk to add to cache
     */
    void TryAppendToCache(Chunk chunk)
    {
        bool chunkHasWater = false;
        Chunk waterChunk;
        //Iterate through list of cached water chunks
        for(auto & cachedWaterChunk : cachedWaterChunks)
        {
            //If water was found, set variable waterChunk to found water chunk.
            if(cachedWaterChunk.equals(chunk.pos.x, chunk.pos.z))
            {
                chunkHasWater = true;
                waterChunk = cachedWaterChunk;
            }
        }
        //If no water was found, create water for @chunk position
        if(!chunkHasWater)
        {
            waterChunk = Chunk(chunk, 3);
        }

        //Adds waterChunk to cache
        cachedWaterChunks.insert(cachedWaterChunks.end(), waterChunk);
        //Adds chunk to cache
        cachedChunks.insert(cachedChunks.end(), chunk);

        //Adds water chunk to world-water vertices
        water.insert(water.end(), waterChunk.vertices.begin(), waterChunk.vertices.end());
        //Adds chunk to world vertices
        world.insert(world.end(), chunk.vertices.begin(), chunk.vertices.end());

        //While world size exceeds 20m. Delete tails of cached chunk
        while(world.size() > 20000000)
        {
            world.erase(world.begin(), world.begin()+cachedChunks[0].vertices.size());
            cachedChunks.erase(cachedChunks.begin());
            water.erase(water.begin(), water.begin()+cachedWaterChunks[0].vertices.size());
            cachedWaterChunks.erase(cachedWaterChunks.begin());
        }


    }

    private:
    std::vector<Chunk> cachedChunks;
    std::vector<Chunk> cachedWaterChunks;

    //Which chunk player is in. Example, if he's in the 3rd created chunk, he would be in 0,3.
    glm::vec2 playerChunkPos;
};


#endif //MIKECRAFT_CHUNKMANAGER_H
