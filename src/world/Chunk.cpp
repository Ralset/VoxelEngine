#include "world/Chunk.h"

#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBufferLayout.h"

Chunk::Chunk(int x,int y)
: m_x(x), m_y(y), m_blocks{}
{
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            for(int h=0;h<5;h++){
                m_blocks[h][i][j]=1;
            }    
        }
    }
    buildMesh();
}

void Chunk::buildMesh()
{
    for(int x=0;x<16;x++){
        for(int y=0;y<256;y++){
            for(int z=0;z<16;z++){
                if(m_blocks[x][y][z]==0)continue;
                //proveri svaki face +x -x +y -y +z -z i bounds takodje
                //edge face prikazujemo ZA SADA jer ne racunamo druge cankove u ovaj racun pa je default prikazivanje
                if(x==0) {}
                else if(x==16) {}
                else {}

                if(z==0) {}
                else if(z==16) {}
                else {}

                if(y==0) {}
                else if(y==256) {}
                else {}
            }
        }
    }
}