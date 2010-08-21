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

#include <string>
#include "colossus_common.h"
#include "backend/GL/mesh_md2_gl.h"
#include "md2_loader.h"

MeshMD2GL::MeshMD2GL(FrameManager* pFrameManager, const std::string& Name) : BaseMeshGL(pFrameManager, Name)
{
    m_meshList = 0;
}

MeshMD2GL::~MeshMD2GL()
{
    if (m_meshList != 0) {
        glDeleteLists(m_meshList, 1);
    }
}


ColossusErrors::COLOSSUS_ERROR MeshMD2GL::Load(const std::string& FileName)
{
    MD2Loader MD2(FileName);

    m_meshList = glGenLists(1);

    glNewList(m_meshList, GL_COMPILE);

    const MD2Loader::Triangle* pTriangles = MD2.GetTriangles();

    glBegin(GL_TRIANGLES);

    const Vector3f* pVertex   = NULL;
    const Vector3f* pNormal   = NULL;
    const Vector2f* pTexCoord = NULL;

    for (unsigned int i = 0 ; i < MD2.GetTriangleCount() ; i++)
    {
        pVertex   = MD2.GetVertex(0, pTriangles[i].VertIndices[0]);
        pTexCoord = MD2.GetTexCoord(pTriangles[i].TexIndices[0]);
        pNormal   = MD2.GetNormal(0, pTriangles[i].VertIndices[0]);

        glTexCoord2f(pTexCoord->x, pTexCoord->y);
        glVertex3f(pVertex->x, pVertex->y, pVertex->z);
        
        glNormal3f(pNormal->x, pNormal->y, pNormal->z);

        pVertex   = MD2.GetVertex(0, pTriangles[i].VertIndices[1]);
        pTexCoord = MD2.GetTexCoord(pTriangles[i].TexIndices[1]);
        pNormal   = MD2.GetNormal(0, pTriangles[i].VertIndices[1]);

        glTexCoord2f(pTexCoord->x, pTexCoord->y);
        glVertex3f(pVertex->x, pVertex->y, pVertex->z);
        
        glNormal3f(pNormal->x, pNormal->y, pNormal->z);

        pVertex   = MD2.GetVertex(0, pTriangles[i].VertIndices[2]);
        pTexCoord = MD2.GetTexCoord(pTriangles[i].TexIndices[2]);
        pNormal   = MD2.GetNormal(0, pTriangles[i].VertIndices[2]);

        glTexCoord2f(pTexCoord->x, pTexCoord->y);        
        glVertex3f(pVertex->x, pVertex->y, pVertex->z);
        
        glNormal3f(pNormal->x, pNormal->y, pNormal->z);
    }

    glEnd();

    glEndList();

    const int loc = FileName.find_last_of('/');
    assert(loc != -1);
    const std::string BaseDir = FileName.substr(0, loc);
    const std::string TextureFileName = BaseDir + "/" + MD2.GetTextureFileName();

    ColossusErrors::COLOSSUS_ERROR ErrorCode = m_texture.Load2D(TextureFileName);

    if (ErrorCode == ColossusErrors::NO_ERROR) {
        SetColorMap(&m_texture);
    }
    else {
        assert(0);
    }

    return ErrorCode;
}

void MeshMD2GL::Render()
{
    glCallList(m_meshList);
}