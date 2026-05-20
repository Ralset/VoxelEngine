#include "world/World.h"

#include "world/Chunk.h"
#include <algorithm>

#include <iostream>

World::World(unsigned int worldSize)
{
    //chunk coordinates ide od -(worldSize+1)/2 do (worldSize+1)/2
    m_worldSize = std::min(maxWorldSize, std::max(1u, worldSize));
    m_minusAxisBound =  -((int)worldSize+1)/2;
    m_plusAxisBound =  worldSize/2;
    GenerateChunks();
}

World::~World(){
    for(int x=0;x<m_worldSize;x++){
        for(int z=0;z<m_worldSize;z++){
            delete m_chunks[x][z];
        }
    }
}

void World::forEachChunk(std::function<void(const Chunk&)> callback) const{
    for(int x=0;x<m_worldSize;x++){
        for(int z=0;z<m_worldSize;z++){
            callback(*m_chunks[x][z]);
        }
    }
}


void World::GenerateChunks(){
    for(int x=0;x<m_worldSize;x++){
        for(int z=0;z<m_worldSize;z++){
            m_chunks[x][z] = new Chunk(x+m_minusAxisBound,z+m_minusAxisBound);
        }
    }
}