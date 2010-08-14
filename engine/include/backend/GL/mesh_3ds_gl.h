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


#ifndef _3DS_MESH_
#define _3DS_MESH_

#include <list>
#include <lib3ds/file.h>

#include "interfaces/colossus_errors.h"
#include "interfaces/colossus_math.h"
#include "base_mesh_gl.h"

class Mesh3DSGL : public BaseMeshGL
{
public:
    Mesh3DSGL(FrameManager* pFrameManager, const std::string& Name);

    ~Mesh3DSGL();

    ColossusErrors::COLOSSUS_ERROR Load(const std::string& pFilename);

    void Render();

private:
   // void CalcNormals(const GLint* pIndices, const Vector3f* pVertices, Vector3f* pNormals);
    void CalcTangents(const Vector3f* pVertices,
                      const Vector2f* pTexels,
                      Vector3f* pTangents,
                      Vector3f* pBitangents);

    struct MeshData
    {
            unsigned int vertexStart;
            unsigned int vertexCount;
            Matrix4f transMatrix;
    };

    typedef std::list<MeshData> MeshList;

    MeshList m_meshes;

    unsigned int m_indexCount;
    unsigned int m_vertexCount;
    unsigned int m_meshCount;

    //GLuint m_indexVBO;
    GLuint m_vertexVBO;
    GLuint m_normalVBO;
    GLuint m_colorVBO;
    GLuint m_texelVBO;
    GLuint m_tangentVBO;
    GLuint m_bitangentVBO;
};

#endif
