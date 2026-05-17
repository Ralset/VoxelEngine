#pragma once

class IndexBuffer{
    public:
        IndexBuffer(const void* data, unsigned int size, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
        inline unsigned int GetCount() const { return m_count; };
    private:
        unsigned int m_RendererID;
        unsigned int m_count;
};