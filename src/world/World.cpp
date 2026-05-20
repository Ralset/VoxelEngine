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

unsigned int World::getBlock(int x, int y, int z){
    int chunkX=x/16, chunkZ=z/16;
    int inChunkX=((x%16)+16)%16, inChunkY=y, inChunkZ=((z%16)+16)%16;
    return m_chunks[chunkX][chunkZ]->getBlockID(inChunkX, inChunkY, inChunkZ);
}

glm::vec3 World::DDA(glm::vec3 startPosition, glm::vec3 direction, const float reach){
    std::cout<<"DDA called"<<std::endl;
    int currX=std::floor(startPosition.x);
    int currY=std::floor(startPosition.y);
    int currZ=std::floor(startPosition.z);

    int prevX=currX;
    int prevY=currY;
    int prevZ=currZ;
    
    int stepX = (direction.x > 0) ? 1 : (direction.x == 0 ? 0 : -1);
    int stepY = (direction.y > 0) ? 1 : (direction.y == 0 ? 0 : -1);
    int stepZ = (direction.z > 0) ? 1 : (direction.z == 0 ? 0 : -1);

    float dX = (direction.x == 0) ? FLT_MAX : std::abs(1.0f / direction.x);
    float dY = (direction.y == 0) ? FLT_MAX : std::abs(1.0f / direction.y);
    float dZ = (direction.z == 0) ? FLT_MAX : std::abs(1.0f / direction.z);

    float untilX, untilY, untilZ;
    
    if(direction.x == 0) untilX = FLT_MAX;
    else if(direction.x > 0) untilX = ((currX + 1.0f) - startPosition.x) * dX;
    else untilX = (startPosition.x - currX) * dX;
    
    if(direction.y == 0) untilY = FLT_MAX;
    else if(direction.y > 0) untilY = ((currY + 1.0f) - startPosition.y) * dY;
    else untilY = (startPosition.y - currY) * dY;
    
    if(direction.z == 0) untilZ = FLT_MAX;
    else if(direction.z > 0) untilZ = ((currZ + 1.0f) - startPosition.z) * dZ;
    else untilZ = (startPosition.z - currZ) * dZ;

    if(direction.x==0)

    if(getBlock(currX, currY, currZ) != 0)
        return glm::vec3(currX, currY, currZ);

    while(std::min({untilX, untilY, untilZ})<=reach){
        if(untilX <= untilY && untilX <= untilZ){
            if(untilX > reach) break;
            prevX = currX;
            currX += stepX;
            untilX += dX;
        }
        else if(untilY <= untilZ){
            if(untilY > reach) break;
            prevY = currY;
            currY += stepY;
            untilY += dY;
        }
        else{
            if(untilZ > reach) break;
            prevZ = currZ;
            currZ += stepZ;
            untilZ += dZ;
        }
        if(getBlock(currX, currY, currZ) != 0)
            return glm::vec3(currX, currY, currZ);

    }
    return glm::vec3(FLT_MAX, 0.0f, 0.0f);
}