#pragma once

#include <functional>

class Chunk;

class World{
    public:
        World(unsigned int worldSize);
        ~World();
        void forEachChunk(std::function<void(const Chunk&)> callaback) const;
    private:
        static constexpr unsigned int maxWorldSize = 16;
        unsigned int m_worldSize;
        int m_minusAxisBound;
        int m_plusAxisBound;
        Chunk* m_chunks[maxWorldSize][maxWorldSize];

        void GenerateChunks();
};