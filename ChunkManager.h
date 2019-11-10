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

    std::vector<Chunk> cachedChunks;

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

    std::vector<float> world1; //Cache

    glm::vec2 playerChunkPos; //Which chunk player is in. Example, if he's in the 3rd created chunk, he would be in 0,3.

    bool hasPlayerMoved = false;

    long seed;

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
        Chunk nwChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
        Chunk neChunk = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
        Chunk seChunk = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
        Chunk swChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
        Chunk nChunk = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ+CHUNK_WIDTH), seed);
        Chunk sChunk = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ-CHUNK_WIDTH), seed);
        Chunk eChunk = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ), seed);
        Chunk wChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ), seed);
        Chunk cChunk = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ), seed);

        InsertIntoCache(nwChunk);
        InsertIntoCache(neChunk);
        InsertIntoCache(seChunk);
        InsertIntoCache(swChunk);
        InsertIntoCache(nChunk);
        InsertIntoCache(sChunk);
        InsertIntoCache(eChunk);
        InsertIntoCache(wChunk);
        InsertIntoCache(cChunk);

        se.insert(se.end(), seChunk.vertices.begin(), seChunk.vertices.end());
        sw.insert(sw.end(), swChunk.vertices.begin(), swChunk.vertices.end());
        nw.insert(nw.end(), nwChunk.vertices.begin(), nwChunk.vertices.end());
        ne.insert(ne.end(), neChunk.vertices.begin(), neChunk.vertices.end());
        w.insert(w.end(), wChunk.vertices.begin(), wChunk.vertices.end());
        e.insert(e.end(), eChunk.vertices.begin(), eChunk.vertices.end());
        s.insert(s.end(), sChunk.vertices.begin(), sChunk.vertices.end());
        n.insert(n.end(), nChunk.vertices.begin(), nChunk.vertices.end());
        c.insert(c.end(), cChunk.vertices.begin(), cChunk.vertices.end());
        world1.insert(world1.end(), se.begin(), se.end());
    }

        void generateChunk(GenerateDirection direction, int chunkPosX, int chunkPosZ)
        {
            std::vector<float> lastNW = nw;
            std::vector<float> lastNE = ne;
            std::vector<float> lastSW = sw;
            std::vector<float> lastSE = se;
            std::vector<float> lastS = s;
            std::vector<float> lastW = w;
            std::vector<float> lastE = e;
            std::vector<float> lastN = n;
            std::vector<float> lastC = c;
            if(direction == RIGHT)
            {
                // if LEFT, generate SW, W, NW
                c=lastW;
                n=lastNW;
                s=lastSW;
                ne = lastN;
                e = lastC;
                se = lastS;

                Chunk swChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
                Chunk wChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ), seed);
                Chunk nwChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
                InsertIntoCache(swChunk);
                InsertIntoCache(wChunk);
                InsertIntoCache(nwChunk);



                sw.clear();
                w.clear();
                nw.clear();
                sw.insert(sw.end(), swChunk.vertices.begin(), swChunk.vertices.end());
                w.insert(w.end(), wChunk.vertices.begin(), wChunk.vertices.end());
                nw.insert(nw.end(), nwChunk.vertices.begin(), nwChunk.vertices.end());
            }

            if(direction == LEFT)
            {
                // if RIGHT, generate SE, E, NE
                c=lastE;
                n=lastNE;
                s=lastSE;
                nw = lastN;
                w = lastC;
                sw = lastS;
                Chunk seChunk = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
                Chunk eChunk = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ), seed);
                Chunk neChunk = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
                InsertIntoCache(seChunk);
                InsertIntoCache(eChunk);
                InsertIntoCache(neChunk);




                se.clear();
                e.clear();
                ne.clear();
                se.insert(se.end(), seChunk.vertices.begin(), seChunk.vertices.end());
                e.insert(e.end(), eChunk.vertices.begin(), eChunk.vertices.end());
                ne.insert(ne.end(), neChunk.vertices.begin(), neChunk.vertices.end());
            }
            if(direction == UP)
            {
                // if up, generate NW, N, NE
                c = lastN;
                w = lastNW;
                e = lastNE;
                sw = lastW;
                s = lastC;
                se = lastE;
                Chunk nwChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
                Chunk nChunk = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ+CHUNK_WIDTH), seed);
                Chunk neChunk = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ+CHUNK_WIDTH), seed);
                InsertIntoCache(nwChunk);
                InsertIntoCache(nChunk);
                InsertIntoCache(neChunk);


                nw.clear();
                n.clear();
                ne.clear();
                nw.insert(nw.end(), nwChunk.vertices.begin(), nwChunk.vertices.end());
                n.insert(n.end(), nChunk.vertices.begin(), nChunk.vertices.end());
                ne.insert(ne.end(), neChunk.vertices.begin(), neChunk.vertices.end());
            }
            if(direction == DOWN)
            {
                // if down, generate SW, S, SE
                c = lastS;
                w = lastSW;
                e = lastSE;
                nw = lastW;
                n = lastC;
                ne = lastE;
                Chunk swChunk = Chunk(glm::vec3(chunkPosX-CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
                Chunk sChunk = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ-CHUNK_WIDTH), seed);
                Chunk seChunk = Chunk(glm::vec3(chunkPosX+CHUNK_WIDTH, 0, chunkPosZ-CHUNK_WIDTH), seed);
                InsertIntoCache(swChunk);
                InsertIntoCache(sChunk);
                InsertIntoCache(seChunk);



                sw.clear();
                s.clear();
                se.clear();
                sw.insert(sw.end(), swChunk.vertices.begin(), swChunk.vertices.end());
                s.insert(s.end(), sChunk.vertices.begin(), sChunk.vertices.end());
                se.insert(se.end(), seChunk.vertices.begin(), seChunk.vertices.end());
            }


            //std::vector<float> lastWorld;
            //lastWorld.insert(lastWorld.begin(), world1.begin()+((int)(world1.size()/8)), world1.end());
            //world1 = lastWorld;


            hasPlayerMoved = true;

        /*
         *
         *
        Chunk chunk = Chunk(glm::vec3(chunkPosX, 0, chunkPosZ), seed);
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
        */
    }

    void InsertIntoCache(Chunk chunk)
    {
        bool chunkAlreadyExists = false;
        for(int x = 0; x < cachedChunks.size(); ++x)
        {
            if(cachedChunks[x].pos.x == chunk.pos.x && cachedChunks[x].pos.z == chunk.pos.z)
            {
                chunkAlreadyExists = true;
            }
        }
        if(!chunkAlreadyExists)
        {
            cachedChunks.insert(cachedChunks.begin(), chunk);
            world1.insert(world1.end(), chunk.vertices.begin(), chunk.vertices.end());
            while(cachedChunks.size() > 27){
                world1.erase(world1.begin(),world1.begin()+cachedChunks[0].vertices.size());
                cachedChunks.erase(cachedChunks.begin());
            }
        }
    }


};


#endif //MIKECRAFT_CHUNKMANAGER_H
