#pragma once

#include <memory>
#include <vector>

class VertexArray;
class IndexBuffer;
class VertexBuffer;

class Chunk{
    public:
        Chunk(int x, int y);
        ~Chunk();
        void UpdateBlock(int x,int y);

        const VertexArray& getVAO() const;
        const IndexBuffer& getEBO() const;

    private:
        void buildMesh();
        void addFace(std::vector<float>& vertices, std::vector<unsigned int>& indices, float x, float y, float z, int face); 
        unsigned int m_blocks[16][256][16];
        int m_x;
        int m_y;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_EBO;
};