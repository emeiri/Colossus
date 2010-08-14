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
    MD2Loader(const std::string& fileName);

    ~MD2Loader();

    unsigned int GetVertexCount();

    const Vector3f* GetVertices();

private:

    void LoadFrames();
    void LoadTriangles();
    void LoadTextureNames();
    void LoadTextureCoords();

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

        Frame(unsigned int NumVertices);

        ~Frame();
    };

    struct Triangle
    {
        unsigned int VertIndices[3];
        unsigned int TexIndices[3];
    };

    struct TexCoord
    {
        float u;
        float v;
    };

    MD2Header m_header;
    Frame** m_ppFrames;
    Triangle* m_pTriangles;
    TexCoord* m_pTexCoords;
    std::list<std::string> m_textureNames;
    int m_fileHandle;
};

#endif	/* _MD2_LOADER_H */

