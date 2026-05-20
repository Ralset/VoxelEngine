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
        std::unique_ptr<Shader> m_shader;
    private:
        
};