#include "world/World.h"

#include "world/Chunk.h"
#include <algorithm>

#include <iostream>

World::World(unsigned int worldSize)
{
    m_worldSize = std::min(maxWorldSize, std::max(1u, worldSize));
    m_minusAxisBound = -static_cast<int>(m_worldSize / 2);
    m_plusAxisBound = m_minusAxisBound + static_cast<int>(m_worldSize) - 1;   
    std::cout<<m_minusAxisBound<<' '<<m_plusAxisBound<<'\n';
    GenerateChunks();
}

World::~World(){
    for(int x=0;x<m_worldSize;x++){
        for(int z=0;z<m_worldSize;z++){
            delete m_chunks[x][z];
        }
    }
}

void World::Update(){
    while(!m_dirtyChunks.empty()){
        std::pair<int,int> xz = m_dirtyChunks.front();
        m_dirtyChunks.pop();
        m_chunks[xz.first][xz.second]->buildMesh();
        //std::cout<<"Updating chunk : ("<<xz.first<<", "<<xz.second<<")"<<std::endl;
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

void World::destroyBlock(glm::vec3 startPosition, glm::vec3 direction, const float reach){
    DDAta data = DDA(startPosition, direction, reach);
    int chunkX=floor(static_cast<float>(data.currentX)/16) - m_minusAxisBound, chunkZ=floor(static_cast<float>(data.currentZ)/16) - m_minusAxisBound;
    int inChunkX=((data.currentX%16)+16)%16, inChunkY=data.currentY, inChunkZ=((data.currentZ%16)+16)%16;
    //std::cout<<"Destroying a block in chunk ("<<chunkX<<", "<<chunkZ<<")"<<std::endl;
    //std::cout<<"at coords ("<<inChunkX<<", "<<inChunkY<<", "<<inChunkZ<<")"<<std::endl;
    if(chunkX < 0 || chunkZ < 0 || chunkX >=m_worldSize || chunkZ >= m_worldSize) return;
    m_chunks[chunkX][chunkZ]->setBlockID(0, inChunkX, inChunkY, inChunkZ);
    m_dirtyChunks.push({chunkX, chunkZ});
}

void World::placeBlock(glm::vec3 startPosition, glm::vec3 direction, const float reach){
    DDAta data = DDA(startPosition, direction, reach);
    int chunkX=floor(static_cast<float>(data.previousX)/16) - m_minusAxisBound, chunkZ=floor(static_cast<float>(data.previousZ)/16) - m_minusAxisBound;
    int inChunkX=((data.previousX%16)+16)%16, inChunkY=data.previousY, inChunkZ=((data.previousZ%16)+16)%16;
    if(chunkX < 0 || chunkZ < 0 || chunkX >=m_worldSize || chunkZ >= m_worldSize) return;
    m_chunks[chunkX][chunkZ]->setBlockID(1, inChunkX, inChunkY, inChunkZ);
    m_dirtyChunks.push({chunkX, chunkZ});
}


unsigned int World::getBlock(int x, int y, int z){
    int chunkX=floor(static_cast<float>(x)/16) - m_minusAxisBound, chunkZ=floor(static_cast<float>(z)/16) - m_minusAxisBound;
    int inChunkX=((x%16)+16)%16, inChunkY=y, inChunkZ=((z%16)+16)%16;
    if(chunkX < 0 || chunkZ < 0 || chunkX >=m_worldSize || chunkZ >= m_worldSize) return 0;
    return m_chunks[chunkX][chunkZ]->getBlockID(inChunkX, inChunkY, inChunkZ);
}

DDAta World::DDA(glm::vec3 startPosition, glm::vec3 direction, const float reach) {
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

    if(getBlock(currX, currY, currZ) != 0){
        return {
            false,
            INT_MAX, INT_MAX, INT_MAX,
            INT_MAX, INT_MAX, INT_MAX
        };
    }

    while(std::min({untilX, untilY, untilZ})<=reach){
        prevX=currX;
        prevY=currY;
        prevZ=currZ;

        if(untilX <= untilY && untilX <= untilZ){
            if(untilX > reach) break;
            currX += stepX;
            untilX += dX;
        }
        else if(untilY <= untilZ){
            if(untilY > reach) break;
            currY += stepY;
            untilY += dY;
        }
        else{
            if(untilZ > reach) break;
            currZ += stepZ;
            untilZ += dZ;
        }
        if(getBlock(currX, currY, currZ) != 0){
            return {
                true,
                currX, currY, currZ,
                prevX, prevY, prevZ
            };
        }
    }
    return {
        false,
        INT_MAX, INT_MAX, INT_MAX,
        INT_MAX, INT_MAX, INT_MAX
    };
}