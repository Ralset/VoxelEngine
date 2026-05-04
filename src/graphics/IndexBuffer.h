#pragma once

class IndexBuffer{
    public:
        IndexBuffer(const void* data, unsigned int size);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
    private:
        unsigned int m_RendererID;
};