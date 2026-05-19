#pragma once

class Chunk{
    public:
        Chunk(int x, int y);
        void UpdateBlock(int x,int y);

    private:
        void buildMesh();
        unsigned int m_blocks[16][256][16];
        int m_x;
        int m_y;
        
};