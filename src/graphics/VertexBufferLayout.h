#pragma once

#include <vector>
#include <glad/glad.h>

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    bool normalized;
    unsigned int getStride() const{
        switch(type){
            case GL_UNSIGNED_INT: return count * sizeof(unsigned int);
            case GL_FLOAT: return count * sizeof(float);
            case GL_UNSIGNED_BYTE: return count * sizeof(unsigned char);
            default: return 0;
        }
    }
};

class VertexBufferLayout{
    public:
        VertexBufferLayout():m_Stride(0){};
        template<typename T>
        void Push(unsigned int count){
            static_assert(false);
        }
        inline const std::vector<VertexBufferElement>& GetElements() const& { return m_Elements; }
        inline const unsigned int GetStride() const { return m_Stride; }
    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
        
};

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count){
    m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
    m_Stride += count * sizeof(unsigned int);
}
template<>
inline void VertexBufferLayout::Push<float>(unsigned int count){
    m_Elements.push_back({ GL_FLOAT, count, false });
    m_Stride += count * sizeof(float);
}
template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count){
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
    m_Stride += count * sizeof(unsigned char);
}
