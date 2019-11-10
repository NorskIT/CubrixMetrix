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

    /*
     * [NW][N ][NE]
     * [W ][C ][E ]
     * [SW][S ][SE]
     */
    enum CenterPosition {

        NW=0,
        N=1,
        NE=2,
        W=3,
        C=4,
        E=5,
        SW=6,
        S=7,
        SE=8
    };

public:

    std::vector<Chunk> cachedChunks;
    Chunk centerChunks[9];
    Chunk water;

    std::vector<float> world1; //Cache

    glm::vec2 playerChunkPos; //Which chunk player is in. Example, if he's in the 3rd created chunk, he would be in 0,3.

    bool hasPlayerMoved = false;

    long seed;

    int i = 0;

    ChunkManager() = default;
    ChunkManager(glm::vec3 playerPos)
    {
        startupGenerateChunk(playerPos);
        seed = 1; //rand()%(1000000-0 + 1);
        std::cout << "seed: " << seed << std::endl;
    }

    void CheckWherePlayerPosition(glm::vec3 playerPos)
    {

        /* To find First X and Z of chunk the player stands in, we have to divide
         * the players X and Y coord by 16, so that we know how many chunk out of world
         * center we are, then we multiply by 16, so that we get the exact X and Y coord
         * of 0,0 of current chunk
         */
        int currentPlayerChunkX= (int)((floor(playerPos.x))/CHUNK_WIDTH)*CHUNK_WIDTH;
        int currentPlayerChunkZ= (int)((floor(playerPos.z)) / CHUNK_WIDTH) * CHUNK_WIDTH;
        if(playerPos.x < 0) {
            currentPlayerChunkX -= CHUNK_WIDTH;
        }if(playerPos.z < 0) {
            currentPlayerChunkZ -= CHUNK_WIDTH;
        }


        if(currentPlayerChunkX < playerChunkPos.x)
        {
            generateChunk(RIGHT, currentPlayerChunkX, currentPlayerChunkZ);
            std::cout << "Player move RIGHT to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkZ << std::endl;
        }
        if(currentPlayerChunkX > playerChunkPos.x)
        {
            generateChunk(LEFT, currentPlayerChunkX, currentPlayerChunkZ);
            std::cout << "Player move LEFT to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkZ << std::endl;
        }
        if(currentPlayerChunkZ > playerChunkPos.y)
        {
            generateChunk(UP, currentPlayerChunkX, currentPlayerChunkZ);
            std::cout << "Player move UP to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkZ << std::endl;
        }
        if(currentPlayerChunkZ < playerChunkPos.y)
        {
            generateChunk(DOWN, currentPlayerChunkX, currentPlayerChunkZ);
            std::cout << "Player move DOWN to chunk: " << currentPlayerChunkX << ", " << currentPlayerChunkZ << std::endl;
        }
        if(playerChunkPos.x != currentPlayerChunkX || playerChunkPos.y != currentPlayerChunkZ)
        {
            std::cout << "Player has move into a different chunk" << std::endl;
            std::cout << "World1 size: " << world1.size() << std::endl;
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
        centerChunks[NW] = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
        centerChunks[N] = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ+CHUNK_WIDTH), seed);
        centerChunks[NE] = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
        centerChunks[W] = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ), seed);
        centerChunks[C] = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ), seed);
        centerChunks[E] = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ), seed);
        centerChunks[SW] = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
        centerChunks[S] = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ-CHUNK_WIDTH), seed);
        centerChunks[SE] = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
        for(Chunk cc : centerChunks)
        {
            InsertIntoCache(cc);
        }
    }

        void generateChunk(GenerateDirection direction, int chunkPosX, int chunkPosZ)
        {
            Chunk lastNW = centerChunks[NW];
            Chunk lastNE = centerChunks[NE];
            Chunk lastSW = centerChunks[SW];
            Chunk lastSE = centerChunks[SE];
            Chunk lastS = centerChunks[S];
            Chunk lastW = centerChunks[W];
            Chunk lastE = centerChunks[E];
            Chunk lastN = centerChunks[N];
            Chunk lastC = centerChunks[C];
            if(direction == RIGHT)
            {
                // if LEFT, generate SW, W, NW
                Chunk swChunk = createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
                Chunk wChunk = createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ), seed);
                Chunk nwChunk = createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
                centerChunks[C ] = lastW;
                centerChunks[N ] = lastNW;
                centerChunks[S ] = lastSW;
                centerChunks[NE] = lastN;
                centerChunks[E ] = lastC;
                centerChunks[SE] = lastS;
                centerChunks[SW] = swChunk;
                centerChunks[W ] = wChunk;
                centerChunks[NW] = nwChunk;
            }

            if(direction == LEFT)
            {
                // if RIGHT, generate SE, E, NE
                Chunk seChunk = createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
                Chunk eChunk = createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ), seed);
                Chunk neChunk = createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
                centerChunks[C ]=lastE;
                centerChunks[N ]=lastNE;
                centerChunks[S ]=lastSE;
                centerChunks[NW] = lastN;
                centerChunks[W ] = lastC;
                centerChunks[SW] = lastS;
                centerChunks[SE] = seChunk;
                centerChunks[E ] = eChunk;
                centerChunks[NE] = neChunk;
            }
            if(direction == UP)
            {
                // if up, generate NW, N, NE
                Chunk nwChunk = createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
                Chunk nChunk = createChunk(glm::vec3(chunkPosX, 0, chunkPosZ+CHUNK_WIDTH), seed);
                Chunk neChunk = createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
                centerChunks[C ] = lastN;
                centerChunks[W ] = lastNW;
                centerChunks[E ] = lastNE;
                centerChunks[SW] = lastW;
                centerChunks[S ] = lastC;
                centerChunks[SE] = lastE;
                centerChunks[NW] = nwChunk;
                centerChunks[N ] = nChunk;
                centerChunks[NE] = neChunk;
            }
            if(direction == DOWN)
            {
                // if down, generate SW, S, SE
                Chunk swChunk = createChunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
                Chunk sChunk = createChunk(glm::vec3(chunkPosX, 0, chunkPosZ-CHUNK_WIDTH), seed);
                Chunk seChunk = createChunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
                centerChunks[C ] = lastS;
                centerChunks[W ] = lastSW;
                centerChunks[E ] = lastSE;
                centerChunks[NW ] = lastW;
                centerChunks[N ] = lastC;
                centerChunks[NE] = lastE;
                centerChunks[SW] = swChunk;
                centerChunks[S ] = sChunk;
                centerChunks[SE] = seChunk;
            }
            for(Chunk cc : centerChunks)
            {
                InsertIntoCache(cc);
            }
            hasPlayerMoved = true;
    }

    /*
     * This methods will first check if the chunk we want to create exists within the cache.
     * if it does, then we will return that chunk. If not, then we will create a new chunk.
     */
    Chunk createChunk(glm::vec3 pos, long seed)
    {
        for(int x = 0; x < cachedChunks.size(); ++x)
        {
            if(cachedChunks[x].equals(pos.x, pos.z))
            {
                return cachedChunks[x];
            }
        }
        return Chunk(glm::vec3(pos.x, pos.y, pos.z), seed);
    }


    void InsertIntoCache(Chunk chunk)
    {
        bool chunkAlreadyExists = false;
        //Check if chunk exists in cache, if it does, move that chunk to front row
        for(int x = 0; x < cachedChunks.size(); ++x)
        {
            if(cachedChunks[x].equals(chunk))
            {
                chunkAlreadyExists = true;
                Chunk pend = cachedChunks[x];
                cachedChunks.erase(cachedChunks.begin()+x);
                cachedChunks.insert(cachedChunks.end(), pend);
            }
        }
        //If chunk does not exists in cache, then append chunk to cache.
        if(!chunkAlreadyExists)
        {
            cachedChunks.insert(cachedChunks.end(), chunk);
            world1.insert(world1.end(), chunk.vertices.begin(), chunk.vertices.end());
            while(cachedChunks.size() > 270/2)
            {
                cachedChunks.erase(cachedChunks.begin());
                world1.erase(world1.begin(), world1.begin()+cachedChunks[0].vertices.size());
            }
        }
    }
};


#endif //MIKECRAFT_CHUNKMANAGER_H
