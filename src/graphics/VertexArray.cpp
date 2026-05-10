#include "VertexArray.h"
#include "Renderer.h"

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
    for(unsigned int i=0;i<elements.size();i++){
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, elements[i].getStride(), (const void*)0));
    }
}

void VertexArray::Bind() const{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const{
    GLCall(glBindVertexArray(0));
}