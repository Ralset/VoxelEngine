#pragma once

#include <functional>

#include <glm/glm.hpp>

class Chunk;

class World{
    public:
        World(unsigned int worldSize);
        ~World();
        void forEachChunk(std::function<void(const Chunk&)> callaback) const;
        glm::vec3 DDA(glm::vec3 startPosition, glm::vec3 direction, const float reach);
    private:
        static constexpr unsigned int maxWorldSize = 16;
        unsigned int m_worldSize;
        int m_minusAxisBound;
        int m_plusAxisBound;
        Chunk* m_chunks[maxWorldSize][maxWorldSize];

        void GenerateChunks();
        unsigned int getBlock(int x, int y, int z);
};