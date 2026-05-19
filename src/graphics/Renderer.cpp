#include "graphics/Renderer.h"

#include "graphics/GLUtils.h"
#include "graphics/VertexArray.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Shader.h"

Renderer::Renderer(){
    m_shader = std::make_unique<Shader>("assets/shaders/Vertex.shader", "assets/shaders/Fragment.shader");
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glCullFace(GL_BACK));
    GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
}

Renderer::~Renderer() = default;

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ebo) const{
    m_shader->Bind();
    vao.Bind();
    ebo.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}