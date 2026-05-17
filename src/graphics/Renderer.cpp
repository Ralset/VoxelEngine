#include "Renderer.h"
#include "GLUtils.h"

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) const{
    shader.Bind();
    vao.Bind();
    ebo.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}