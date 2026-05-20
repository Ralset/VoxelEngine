#pragma once

#include <functional>
#include <queue>

#include <glm/glm.hpp>

class Chunk;

struct DDAta{
    bool collision;
    int currentX, currentY, currentZ;
    int previousX, previousY, previousZ;
};


class World{
    public:
        World(unsigned int worldSize);
        ~World();
        void Update();
        void forEachChunk(std::function<void(const Chunk&)> callaback) const;
        inline bool canReachBlock(glm::vec3 startPosition, glm::vec3 direction, const float reach) {
            return DDA(startPosition, direction, reach).collision; 
        };
        void destroyBlock(glm::vec3 startPosition, glm::vec3 direction, const float reach);
        void placeBlock(glm::vec3 startPosition, glm::vec3 direction, const float reach);

    private:
        static constexpr unsigned int maxWorldSize = 16;
        unsigned int m_worldSize;
        std::queue<std::pair<int,int>> m_dirtyChunks;
        int m_minusAxisBound;
        int m_plusAxisBound;
        Chunk* m_chunks[maxWorldSize][maxWorldSize];

        void GenerateChunks();
        unsigned int getBlock(int x, int y, int z);
        DDAta DDA(glm::vec3 startPosition, glm::vec3 direction, const float reach);
};