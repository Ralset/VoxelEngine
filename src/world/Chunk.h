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
        void UpdateBlock(int x,int y);

        const glm::mat4 getModel() const;
        const VertexArray& getVAO() const;
        const IndexBuffer& getEBO() const;

    private:
        void buildMesh();
        void addFace(std::vector<float>& vertices, std::vector<unsigned int>& indices, float x, float y, float z, int face); 
        unsigned int m_blocks[16][256][16];
        int m_x;
        int m_z;
        glm::mat4 m_Model;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_EBO;
};