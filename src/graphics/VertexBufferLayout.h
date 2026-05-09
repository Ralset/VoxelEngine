#pragma once

#include <vector>
#include <glad/glad.h>

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    bool normalized;
};

class VertexBufferLayout{
    public:
        VertexBufferLayout():m_Stride(0){};
        template<typename T>
        void Push(unsigned int count){
            static_assert(false);
        }
        template<>
        void Push<unsigned int>(unsigned int count){
            m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
            m_Stride += count * sizeof(unsigned int);
        }
        template<>
        void Push<float>(unsigned int count){
            m_Elements.push_back({ GL_FLOAT, count, false });
            m_Stride += count * sizeof(float);
        }
        template<>
        void Push<unsigned char>(unsigned int count){
            m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
            m_Stride += count * sizeof(unsigned char);
        }
        inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
        inline const unsigned int GetSride() const { return m_Stride; }
    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
        
};