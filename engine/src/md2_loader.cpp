/*

	Copyright 2010 Etay Meiri

	This file is part of Colossus

    Colossus is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Colosssus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Colosssus.  If not, see <http://www.gnu.org/licenses/>.

*/


#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <exception>

#include "colossus_common.h"
#include "md2_loader.h"


static const int MD2_MAGIC_NUM = 844121161;
static const int MD2_STANDARD_VERSION = 8;

//STATIC_ASSERT(sizeof(MD2Header) == 68);

MD2Loader::Frame::Frame(unsigned int NumVertices)
{
    pPos = new Vector3f[NumVertices];
}

MD2Loader::Frame::~Frame()
{
    delete [] pPos;
}

MD2Loader::MD2Loader(const std::string& fileName)
{
    printf("Opening '%s'\n", fileName.c_str());
    m_fileHandle = open(fileName.c_str(), O_RDONLY);

    if (m_fileHandle < 0)
        throw new std::exception;

    int BytesRead = read(m_fileHandle, &m_header, sizeof(m_header));
    assert(BytesRead == 68);

    if (m_header.MagicNum != MD2_MAGIC_NUM) {
        close(m_fileHandle);
        throw new std::string("'%s' does not have MD2 magic number");
    }

    if (m_header.Version != 8) {
        close(m_fileHandle);
        throw new std::exception;
    }

    LoadFrames();
    LoadTriangles();
    LoadTextureNames();
    LoadTextureCoords();

    close(m_fileHandle);
}


MD2Loader::~MD2Loader()
{
    // allocate individual frames
    for (unsigned int i = 0 ; i < m_header.NumFrames ; i++) {
        delete m_ppFrames[i];
    }

    delete [] m_ppFrames;

    delete [] m_pTriangles;

    delete [] m_pTexCoords;
}

void MD2Loader::LoadFrames()
{
    // allocate frame array
    m_ppFrames = new Frame*[m_header.NumFrames];

    // allocate individual frames
    for (unsigned int i = 0 ; i < m_header.NumFrames ; i++) {
        m_ppFrames[i] = new Frame(m_header.NumVertices);
    }
    
    // load the data of all the frames
    for (unsigned int i = 0 ; i < m_header.NumFrames ; i++) {
        // jump to start of the next frame data
        lseek(m_fileHandle, m_header.FramesOffset + i * m_header.FrameSize, SEEK_SET);

        FrameHeader FrameHeader;
        Frame* pCurrentFrame = m_ppFrames[i];
        int BytesRead = read(m_fileHandle, &FrameHeader, sizeof(FrameHeader));
        assert(BytesRead == sizeof(FrameHeader));

        memcpy(&(pCurrentFrame->Name), FrameHeader.Name, sizeof(FrameHeader.Name));
        
        printf("Loading frame '%s'\n", FrameHeader.Name);
        for (unsigned int j = 0 ; j < m_header.NumVertices ; j++) {
            char Pos[3];
            
            BytesRead = read(m_fileHandle, Pos, sizeof(Pos));
            assert(BytesRead == sizeof(Pos));

            pCurrentFrame->pPos[j].x = (float)Pos[0] * FrameHeader.Scale[0] + FrameHeader.Translation[0];
            pCurrentFrame->pPos[j].y = (float)Pos[1] * FrameHeader.Scale[1] + FrameHeader.Translation[1];
            pCurrentFrame->pPos[j].z = (float)Pos[2] * FrameHeader.Scale[2] + FrameHeader.Translation[2];

            printf("Pos %d: %.02f, %.02f, %.02f\n", j,
                                                    pCurrentFrame->pPos[j].x,
                                                    pCurrentFrame->pPos[j].y,
                                                    pCurrentFrame->pPos[j].z);
        }
    }    
}


void MD2Loader::LoadTriangles()
{
    m_pTriangles = new Triangle[m_header.NumTris];
    
    // jump to the start of the triangle data
    lseek(m_fileHandle, m_header.TrisOffset, SEEK_SET);

    struct Data
    {
        unsigned short VertIndices[3];
        unsigned short TexIndices[3];
    };

    Data t;

    for (unsigned int i = 0 ; i < m_header.NumTris ; i++) {
        int BytesRead = read(m_fileHandle, &t, sizeof(t));
        assert(BytesRead == sizeof(t));

        m_pTriangles[i].VertIndices[0] = t.VertIndices[0];
        m_pTriangles[i].VertIndices[1] = t.VertIndices[1];
        m_pTriangles[i].VertIndices[2] = t.VertIndices[2];

        m_pTriangles[i].TexIndices[0] = t.TexIndices[0];
        m_pTriangles[i].TexIndices[1] = t.TexIndices[1];
        m_pTriangles[i].TexIndices[2] = t.TexIndices[2];

        printf("Triangle %d: vertices %d %d %d tex %d %d %d\n", i,
            m_pTriangles[i].VertIndices[0],
            m_pTriangles[i].VertIndices[1],
            m_pTriangles[i].VertIndices[2],
            m_pTriangles[i].TexIndices[0],
            m_pTriangles[i].TexIndices[1],
            m_pTriangles[i].TexIndices[2]);
    }
}

void MD2Loader::LoadTextureNames()
{
    lseek(m_fileHandle, m_header.SkinOffset, SEEK_SET);

    for (unsigned int i = 0 ; i < m_header.NumSkins ; i++) {
        char Name[64];

        ZeroMem(Name);
        int BytesRead = read(m_fileHandle, Name, sizeof(Name));
        assert(BytesRead == sizeof(Name));
        printf("'%s'\n", Name);

        m_textureNames.push_front(Name);
    }
}


void MD2Loader::LoadTextureCoords()
{
    m_pTexCoords = new TexCoord[m_header.NumTexCoords];
            
    lseek(m_fileHandle, m_header.TexCoordsOffset, SEEK_SET);

    struct Data
    {
        unsigned short u;
        unsigned short v;
    };

    Data t;

    for (unsigned int i = 0 ; i < m_header.NumTexCoords ; i++) {
        int BytesRead = read(m_fileHandle, &t, sizeof(t));
        assert(BytesRead == sizeof(t));
        m_pTexCoords[i].u = (float)t.u / (float)m_header.SkinWidth;
        m_pTexCoords[i].v = (float)t.v / (float)m_header.SkinHeight;
        printf("Tex coords: %d,%d  %.02f,%.02f\n", t.u, t.v, m_pTexCoords[i].u, m_pTexCoords[i].v);
    }
}

