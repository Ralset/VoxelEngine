#pragma once

#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class VertexArray;
class IndexBuffer;
class VertexBuffer;

class Chunk{
    public:
        Chunk(int x, int y);
        ~Chunk();
        void buildMesh();
        
        inline void setBlockID(unsigned int blockID, int x, int y, int z) { m_blocks[x][y][z] = blockID; };
        inline unsigned int getBlockID(int x,int y,int z) const { return m_blocks[x][y][z]; };
        const glm::mat4 getModel() const;
        const VertexArray& getVAO() const;
        const IndexBuffer& getEBO() const;

    private:
        void addFace(std::vector<float>& vertices, std::vector<unsigned int>& indices, float x, float y, float z, int face); 
        unsigned int m_blocks[16][256][16];
        int m_x;
        int m_z;
        glm::mat4 m_Model;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_EBO;
};