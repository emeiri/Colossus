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

#ifndef _MD2_LOADER_H
#define	_MD2_LOADER_H

#include <string>
#include <list>
#include "interfaces/colossus_math.h"

class MD2Loader
{
public:
    struct Triangle
    {
        unsigned int VertIndices[3];
        unsigned int TexIndices[3];
    };

    MD2Loader(const std::string& fileName);

    ~MD2Loader();

    inline unsigned int GetVertexCount() const
    {
        return m_header.NumVertices;
    }

    inline unsigned int GetFrameCount() const
    {
        return m_header.NumFrames;
    }

    inline const Vector3f* GetVertex(unsigned int Frame, unsigned int Vertex) const
    {
        assert(Frame < m_header.NumFrames);
        assert(Vertex < m_header.NumVertices);
        return &(m_ppFrames[Frame]->pPos[Vertex]);
    }

    inline const Vector3f* GetNormal(unsigned int Frame, unsigned int Vertex) const
    {
        assert(Frame < m_header.NumFrames);
        assert(Vertex < m_header.NumVertices);
        return &(m_ppFrames[Frame]->pNormals[Vertex]);
    }

    inline const Vector2f* GetTexCoords() const
    {
        return m_pTexCoords;
    }

    inline const Vector2f* GetTexCoord(unsigned int TexIndex) const
    {
        assert(TexIndex < m_header.NumTexCoords);
        return &(m_pTexCoords[TexIndex]);
    }

    inline const Triangle* GetTriangles() const
    {
        return m_pTriangles;
    }

    inline unsigned int GetTriangleCount() const
    {
        return m_header.NumTris;
    }

    inline std::string GetTextureFileName() const
    {
        return m_textureNames.front();
    }
    
private:

    void LoadFrames(int FileHandle);
    void LoadTriangles(int FileHandle);
    void LoadTextureNames(int FileHandle);
    void LoadTextureCoords(int FileHandle);

    struct MD2Header
    {
        int MagicNum;
        int Version;
        int SkinWidth;
        int SkinHeight;
        int FrameSize;
        int NumSkins;
        int NumVertices;
        int NumTexCoords;
        int NumTris;
        int NumGLcmds;
        int NumFrames;
        int SkinOffset;
        int TexCoordsOffset;
        int TrisOffset;
        int FramesOffset;
        int GLcmdsOffset;
        int FileSize;
    };

    struct FrameHeader
    {
        float Scale[3];
        float Translation[3];
        char Name[16];
    };

    struct Frame
    {
        char Name[16];

        Vector3f* pPos;
        Vector3f* pNormals;

        Frame(unsigned int NumVertices);

        ~Frame();
    };

    MD2Header m_header;
    Frame** m_ppFrames;
    Triangle* m_pTriangles;
    Vector2f* m_pTexCoords;
    std::list<std::string> m_textureNames;
};

#endif	/* _MD2_LOADER_H */

