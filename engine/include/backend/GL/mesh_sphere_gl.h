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

#ifndef _MESH_SPHERE_GL_H
#define	_MESH_SPHERE_GL_H

#include <vector>
#include <string>
#include "frame_manager.h"
#include "base_mesh.h"


class MeshSphereGL : public BaseMeshGL
{
public:
    MeshSphereGL(FrameManager* pFrameManager, 
                 const std::string& Name,
                 float Radius,
                 unsigned int NumSlices,
                 unsigned int NumStacks);

    ColossusErrors::COLOSSUS_ERROR Load(const std::string& FileName);

    void Render();

private:
    struct Vertex
    {
        Vertex(){}
        Vertex(float x, float y, float z,
                float tx, float ty, float tz,
                float nx, float ny, float nz,
                float u, float v)
          //      : pos(x,y,z), tangent(tx, ty, tz), normal(nx,ny,nz), texC(u,v){}
                  : pos(x,y,z), normal(nx,ny,nz), texC(u,v){}

        Vector3f pos;
        //Vector3f tangent;
        Vector3f normal;
        Vector2f texC;
    };

    typedef std::vector<Vertex> VertexList;
    typedef std::vector<GLint> IndexList;

    void BuildStacks(VertexList& vertices, IndexList& indices);

    float m_radius;
    unsigned int m_numSlices;
    unsigned int m_numStacks;
    unsigned int m_numIndices;

    GLuint m_vertexVBO;
    GLuint m_indexVBO;
};


#endif	/* _MESH_SPHERE_GL_H */

