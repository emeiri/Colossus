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


#include <stdio.h>
#include <math.h>
#include "backend/GL/mesh_sphere_gl.h"

#define BUFFER_OFFSET(bytes) ((GLubyte*) NULL + (bytes))

MeshSphereGL::MeshSphereGL(FrameManager* pFrameManager, 
                           const std::string& Name,
                           float Radius,
                           unsigned int NumSlices,
                           unsigned int NumStacks) : BaseMeshGL(pFrameManager, Name)
{
    m_radius    = Radius;
    m_numSlices = NumSlices;
    m_numStacks = NumStacks;

	std::vector<Vertex> vertices;
	std::vector<GLint> indices;

	BuildStacks(vertices, indices);
    m_numIndices = indices.size();

    glGenBuffers(1, &m_vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
    printf("Loading %d vertices into the VB\n", vertices.size());
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size() , &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * m_numIndices, &indices[0], GL_STATIC_DRAW);
}

void MeshSphereGL::BuildStacks(VertexList& vertices, IndexList& indices)
{
	const float phiStep = M_PI / m_numStacks;

	// do not count the poles as rings
	const unsigned int numRings = m_numStacks-1;

	// Compute vertices for each stack ring.
	for(unsigned int i = 1; i <= numRings; ++i)
	{
		float phi = i*phiStep;

		// vertices of ring
		float thetaStep = 2.0f * M_PI / m_numSlices;
		for(unsigned int j = 0; j <= m_numSlices; ++j)
		{
			float theta = j * thetaStep;

			Vertex v;

			// spherical to cartesian
			v.pos.x = m_radius * sinf(phi)*cosf(theta);
			v.pos.y = m_radius * cosf(phi);
			v.pos.z = m_radius * sinf(phi)*sinf(theta);

          //  v.pos.Print();
			// partial derivative of P with respect to theta
/*			v.tangent.x = -m_radius*sinf(phi)*sinf(theta);
			v.tangent.y = 0.0f;
			v.tangent.z = m_radius*sinf(phi)*cosf(theta);
*/
            v.normal = v.pos.Normalize();

			v.texC.x = theta / (2.0f * M_PI);
			//v.texC.y = phi / M_PI;
            v.texC.y = (numRings + 1 - i) / M_PI;

       //     printf("%f %f\n", v.texC.x, v.texC.y);

			vertices.push_back( v );
		}
	}

   // exit(0);
	// poles: note that there will be texture coordinate distortion
	vertices.push_back( Vertex(0.0f, -m_radius, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f) );
	vertices.push_back( Vertex(0.0f, m_radius, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f) );

	const unsigned int northPoleIndex = (unsigned int)vertices.size()-1;
	const unsigned int southPoleIndex = (unsigned int)vertices.size()-2;

	const unsigned int numRingVertices = m_numSlices+1;

	// Compute indices for inner stacks (not connected to poles).
	for(unsigned int i = 0; i < m_numStacks-2; ++i)
	{
		for(unsigned int j = 0; j < m_numSlices; ++j)
		{
			indices.push_back(i*numRingVertices + j);
			indices.push_back(i*numRingVertices + j+1);
			indices.push_back((i+1)*numRingVertices + j);

			indices.push_back((i+1)*numRingVertices + j);
			indices.push_back(i*numRingVertices + j+1);
			indices.push_back((i+1)*numRingVertices + j+1);
		}
	}

	// Compute indices for top stack.  The top stack was written
	// first to the vertex buffer.
	for(unsigned int i = 0; i < m_numSlices; ++i)
	{
		indices.push_back(northPoleIndex);        
		indices.push_back(i+1);
        indices.push_back(i);
		
	}

	// Compute indices for bottom stack.  The bottom stack was written
	// last to the vertex buffer, so we need to offset to the index
	// of first vertex in the last ring.
	unsigned int baseIndex = (numRings-1)*numRingVertices;
	for(unsigned int i = 0; i < m_numSlices; ++i)
	{
		indices.push_back(southPoleIndex);        
		indices.push_back(baseIndex+i);
		indices.push_back(baseIndex+i+1);
	}
}

ColossusErrors::COLOSSUS_ERROR MeshSphereGL::Load(const std::string& FileName)
{
    return ColossusErrors::UNSUPPORTED_OPERATION;
}

void MeshSphereGL::Render()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_INDEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(sizeof(Vector3f)));
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(sizeof(Vector3f) * 2));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexVBO);
    glIndexPointer(GL_UNSIGNED_INT, 0, 0);

//    printf("Drawing %d indices\n", m_numIndices);
    glDrawElements(GL_POLYGON, m_numIndices, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}


