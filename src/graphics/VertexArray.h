#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray{
    public:
        VertexArray();
        ~VertexArray();
        void AddBuffer(VertexBuffer& vbo, VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;
    private:
        unsigned int m_RendererID;
};