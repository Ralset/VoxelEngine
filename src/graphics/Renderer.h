#pragma once

#include <memory>

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer{
    public:
        Renderer();
        ~Renderer();
        void Clear() const;
        void Draw(const VertexArray& vao, const IndexBuffer& ebo) const;
    private:
        std::unique_ptr<Shader> m_shader;
};