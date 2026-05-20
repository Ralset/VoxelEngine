#include "world/Chunk.h"

#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBufferLayout.h"

#include <vector>

#include <stdexcept>

Chunk::Chunk(int x,int z)
: m_x(x), m_z(z), m_blocks{}
{
    m_Model = glm::translate(glm::mat4(1.0f), glm::vec3((float)x*16, 0.0f, (float)z*16));
    m_VAO = std::make_unique<VertexArray>();
    for(int x=0;x<16;x++){
        for(int y=0;y<4;y++){
            for(int z=0;z<16;z++){
                m_blocks[x][y][z]=1;
            }    
        }
    }
    buildMesh();
}

Chunk::~Chunk() = default;

const glm::mat4 Chunk::getModel() const { return m_Model; };
const VertexArray& Chunk::getVAO() const { return *m_VAO; };
const IndexBuffer& Chunk::getEBO() const { return *m_EBO; };

void Chunk::addFace(std::vector<float>& vertices, std::vector<unsigned int>& indices, float x, float y, float z, int face)
{
    unsigned int base = vertices.size() / 3;

    switch (face)
    {
        case 0:
            // -X face - Left face
            vertices.push_back(x);   vertices.push_back(y+1); vertices.push_back(z);
            vertices.push_back(x);   vertices.push_back(y);   vertices.push_back(z);
            vertices.push_back(x);   vertices.push_back(y);   vertices.push_back(z+1);
            vertices.push_back(x);   vertices.push_back(y+1); vertices.push_back(z+1);
            break;
        case 1:
            // +X face - Right face
            vertices.push_back(x+1); vertices.push_back(y);   vertices.push_back(z+1);
            vertices.push_back(x+1); vertices.push_back(y);   vertices.push_back(z);
            vertices.push_back(x+1); vertices.push_back(y+1); vertices.push_back(z);
            vertices.push_back(x+1); vertices.push_back(y+1); vertices.push_back(z+1);
            break;
        case 2:
            // -Z face - Back face
            vertices.push_back(x+1); vertices.push_back(y+1); vertices.push_back(z);
            vertices.push_back(x+1); vertices.push_back(y);   vertices.push_back(z);
            vertices.push_back(x);   vertices.push_back(y);   vertices.push_back(z);
            vertices.push_back(x);   vertices.push_back(y+1); vertices.push_back(z);
            break;
        case 3:
            // +Z face - Front face
            vertices.push_back(x);   vertices.push_back(y);   vertices.push_back(z+1);
            vertices.push_back(x+1); vertices.push_back(y);   vertices.push_back(z+1);
            vertices.push_back(x+1); vertices.push_back(y+1); vertices.push_back(z+1);
            vertices.push_back(x);   vertices.push_back(y+1); vertices.push_back(z+1);
            break;
        case 4:
            // -Y face - Bottom face
            vertices.push_back(x+1); vertices.push_back(y);   vertices.push_back(z);
            vertices.push_back(x+1); vertices.push_back(y);   vertices.push_back(z+1);
            vertices.push_back(x);   vertices.push_back(y);   vertices.push_back(z+1);
            vertices.push_back(x);   vertices.push_back(y);   vertices.push_back(z);
            break;
        case 5:
            // +Y face - Top face
            vertices.push_back(x);   vertices.push_back(y+1); vertices.push_back(z+1);
            vertices.push_back(x+1); vertices.push_back(y+1); vertices.push_back(z+1);
            vertices.push_back(x+1); vertices.push_back(y+1); vertices.push_back(z);
            vertices.push_back(x);   vertices.push_back(y+1); vertices.push_back(z);
            break;
        
        default:
            break;
    }
    indices.push_back(base+0);
    indices.push_back(base+1);
    indices.push_back(base+2);
    indices.push_back(base+2);
    indices.push_back(base+3);
    indices.push_back(base+0);

}

void Chunk::buildMesh()
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for(int x=0;x<16;x++){
        for(int y=0;y<256;y++){
            for(int z=0;z<16;z++){
                if(m_blocks[x][y][z]==0)continue;
                //proveri svaki face +x -x +y -y +z -z i bounds takodje
                //edge face prikazujemo ZA SADA jer ne racunamo druge cankove u ovaj racun pa je default prikazivanje
                if(x == 0) addFace(vertices, indices, x, y, z, 0);
                else if(m_blocks[x-1][y][z] == 0) addFace(vertices, indices, x, y, z, 0);

                if(x == 15) addFace(vertices, indices, x, y, z, 1);
                else if(m_blocks[x+1][y][z] == 0) addFace(vertices, indices, x, y, z, 1);
                
                if(z == 0) addFace(vertices, indices, x, y, z, 2);
                else if(m_blocks[x][y][z-1] == 0) addFace(vertices, indices, x, y, z, 2);
                
                if(z == 15) addFace(vertices, indices, x, y, z, 3);
                else if(m_blocks[x][y][z+1] == 0) addFace(vertices, indices, x, y, z, 3);
                
                if(y == 0) addFace(vertices, indices, x, y, z, 4);
                else if(m_blocks[x][y-1][z] == 0) addFace(vertices, indices, x, y, z, 4);
                
                if(y == 255) addFace(vertices, indices, x, y, z, 5);
                else if(m_blocks[x][y+1][z] == 0) addFace(vertices, indices, x, y, z, 5);
            }
        }
    }

    m_VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    m_VAO->AddBuffer(*m_VBO, layout);

    m_EBO = std::make_unique<IndexBuffer>(indices.data(), (unsigned int)(indices.size() * sizeof(unsigned int)), (unsigned int)indices.size());
}