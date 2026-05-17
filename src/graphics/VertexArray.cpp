#include "VertexArray.h"
#include "GLUtils.h"

VertexArray::VertexArray(){
    GLCall(glGenVertexArrays(1, &m_RendererID));
    GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray(){
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(VertexBuffer& vbo, VertexBufferLayout& layout){
    vbo.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset=0;
    for(unsigned int i=0;i<elements.size();i++){
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.GetStride(), (const void*)(uintptr_t)offset));
        offset += elements[i].getStride();
    }
}

void VertexArray::Bind() const{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const{
    GLCall(glBindVertexArray(0));
}