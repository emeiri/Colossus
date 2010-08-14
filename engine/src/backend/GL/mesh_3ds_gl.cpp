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


#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
#include <lib3ds/types.h>
#include <lib3ds/material.h>
#include <string.h>

#include "colossus_common.h"
#include "backend/GL/mesh_3ds_gl.h"
#include "interfaces/colossus_math.h"


static unsigned int GetFaceCount(const Lib3dsFile* pFile)
{
    unsigned int FaceCount = 0;

    Lib3dsMesh* pMesh = NULL;

    // Loop through every mesh
    for (pMesh = pFile->meshes ; pMesh != NULL ; pMesh = pMesh->next) {
        //printf("Mesh %s, faces %d\n", pMesh->name, pMesh->faces);
        // Add the number of faces this mesh has to the total faces
        FaceCount += pMesh->faces;
    }

    return FaceCount;
}

Mesh3DSGL::Mesh3DSGL(FrameManager* pFrameManager, const std::string& Name) : BaseMeshGL(pFrameManager, Name)
{
    m_vertexCount = 0;
    m_meshCount = 0;
}


Mesh3DSGL::~Mesh3DSGL()
{
}

ColossusErrors::COLOSSUS_ERROR Mesh3DSGL::Load(const std::string& pFilename)
{
    Lib3dsFile* pFile = lib3ds_file_load(pFilename.c_str());

    ColossusErrors::COLOSSUS_ERROR ret = ColossusErrors::NO_ERROR;

    if (!pFile) {
        fprintf(stderr, "Unable to load 3DS file: %s\n", pFilename.c_str());
        ret = ColossusErrors::FILE_NOT_FOUND;
    }
    else {
        const unsigned int FaceCount = GetFaceCount(pFile);
        m_vertexCount = FaceCount * 3;

        //printf("Face count %d\n", FaceCount);

        // Allocate memory for our pVertices and pNormals
        Vector3f* pVertices    = new Vector3f[m_vertexCount];
        Lib3dsVector* pNormals = new Lib3dsVector[m_vertexCount];
        Vector4f* pColors      = new Vector4f[m_vertexCount];
        Vector2f* pTexels      = new Vector2f[m_vertexCount];
        Vector3f* pTangents    = new Vector3f[m_vertexCount];
        Vector3f* pBitangents  = new Vector3f[m_vertexCount];

        Lib3dsMesh* pMesh = NULL;
        unsigned int FinishedFaces = 0;
        unsigned int VertexStart = 0;
        MeshData Mesh;

        // Loop through all the meshes
        for (pMesh = pFile->meshes ; pMesh != NULL ; pMesh = pMesh->next)
        {
            if (pMesh->faces > 0) {
                lib3ds_mesh_calculate_normals(pMesh, &pNormals[FinishedFaces*3]);

                Mesh.vertexStart = VertexStart;
                Mesh.vertexCount = pMesh->faces * 3;

                VertexStart += Mesh.vertexCount;

                //printf("Mesh '%s' vertex start %d vertex count %d\r\n", pMesh->name, Mesh.vertexStart, Mesh.vertexCount);

                for (unsigned int i = 0 ; i < 4 ; i++) {
                    for (unsigned int j = 0 ; j < 4 ; j++) {
                        Mesh.transMatrix.m[j][i] = pMesh->matrix[i][j];
                    }
                    //printf("%f %f %f %f\n", pMesh->matrix[i][0], pMesh->matrix[i][1], pMesh->matrix[i][2], pMesh->matrix[i][3]);
                }

                m_meshes.push_back(Mesh);
                m_meshCount++;

                const char* pMaterialName = pMesh->faceL[0].material;
                //printf("Material: %s\n", pMaterialName);
                Lib3dsMaterial* pMaterial = lib3ds_file_material_by_name(pFile, pMaterialName);

                if (pMaterial) {
                  //  printf("	Ambient: %f, %f, %f, %f\n", pMaterial->ambient[0], pMaterial->ambient[1], pMaterial->ambient[2], pMaterial->ambient[3]);
                    //printf("	Diffuse: %f, %f, %f, %f\n", pMaterial->diffuse[0], pMaterial->diffuse[1], pMaterial->diffuse[2], pMaterial->diffuse[3]);
                    //printf("	Specular: %f, %f, %f, %f\n", pMaterial->specular[0], pMaterial->specular[1], pMaterial->specular[2], pMaterial->specular[3]);
                    if (strlen(pMaterial->texture1_map.name) > 0) {
                        //printf("    Texture: %s\n", pMaterial->texture1_map.name);
                    }
                }

                //printf("Points %d texels %d\n", pMesh->points, pMesh->texels);
                // for each triangle
                for (unsigned int j = 0 ; j < pMesh->faces ; j++)
                {
                    const Lib3dsFace* pFace = &pMesh->faceL[j];

                    for (unsigned int i = 0 ; i < 3 ; i++)
                    {
                        const unsigned int VertexIndex = FinishedFaces * 3 + i;
                        const unsigned int Index = pFace->points[i];
                    //    printf("Vertex index %d index %d\n", VertexIndex, Index);
                        //printf("Vertex addr %x %x\n", &(pVertices[0]), &(pVertices[VertexIndex]));
                        pVertices[VertexIndex].x = pMesh->pointL[Index].pos[0];
                        pVertices[VertexIndex].y = pMesh->pointL[Index].pos[1];
                        pVertices[VertexIndex].z = pMesh->pointL[Index].pos[2];

                        //printf("Texel addr %x\n", &(pTexels[VertexIndex]));
                        //printf("%.02f,%.02f\n", pMesh->texelL[pFace->points[i]][0], pMesh->texelL[pFace->points[i]][1]);
                        if (Index < pMesh->texels) {
                            pTexels[VertexIndex].x = pMesh->texelL[Index][0];
                            pTexels[VertexIndex].y = pMesh->texelL[Index][1];
                        }
                        else {
                            pTexels[VertexIndex].x = 0.0f;
                            pTexels[VertexIndex].y = 0.0f;
                        }

                        if (pMaterial) {
                            for (unsigned int k = 0; k < 4 ; k++) {
                                pColors[VertexIndex].v[k] = pMaterial->diffuse[k];
                            }
                        }
                        else {
                            for (unsigned int k = 0; k < 4 ; k++) {
                                pColors[VertexIndex].v[k] = 0.0f;
                            }
                        }
                    }

                    FinishedFaces++;
                }
            }
        }

        /*for (unsigned int i = 0 ; i < m_vertexCount ; i++) {
                printf("%llx %llx %llx\n", (long long)pNormals[i][0],(long long)pNormals[i][1], (long long)pNormals[i][2]);
                printf("%llx %llx %llx\n", (long long)pColors[i][0],(long long)pColors[i][1], (long long)pColors[i][2]);
        }*/

        //printf("Mesh count: %d\n", m_meshCount);

        CalcTangents(pVertices, pTexels, pTangents, pBitangents);

        glGenBuffers(1, &m_vertexVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * m_vertexCount, pVertices, GL_STATIC_DRAW);

        glGenBuffers(1, &m_normalVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_normalVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * m_vertexCount, pNormals, GL_STATIC_DRAW);

       // glGenBuffers(1, &m_colorVBO);
      //  glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
      //  glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4f) * m_vertexCount, pColors, GL_STATIC_DRAW);

        glGenBuffers(1, &m_texelVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_texelVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2f) * m_vertexCount, pTexels, GL_STATIC_DRAW);

        glGenBuffers(1, &m_tangentVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_tangentVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * m_vertexCount, pTangents, GL_STATIC_DRAW);

        glGenBuffers(1, &m_bitangentVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_bitangentVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * m_vertexCount, pBitangents, GL_STATIC_DRAW);


        delete [] pVertices;
        delete [] pNormals;
        delete [] pColors;
        delete [] pTexels;
        delete [] pTangents;
        delete [] pBitangents;

        lib3ds_file_free(pFile);
    }

    return ret;
}


void Mesh3DSGL::Render()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_INDEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_normalVBO);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_texelVBO);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    //glEnableVertexAttribArray(m_tangentLoc);
    glBindBuffer(GL_ARRAY_BUFFER, m_tangentVBO);
    glVertexAttribPointer(m_tangentLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

//    glBindBuffer(GL_ARRAY_BUFFER, m_bitangentVBO);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    for (MeshList::const_iterator it = m_meshes.begin() ; it != m_meshes.end() ; it++) {
            //glPushMatrix();
            //glTranslatef(it->transMatrix.m[3][0], it->transMatrix.m[3][1], it->transMatrix.m[3][2]);
            //glMultMatrixf((const GLfloat*)&(it->transMatrix.m[0][0]));
        //printf("Drawing %d vertices from %d\n", it->vertexCount, it->vertexStart);
            glDrawArrays(GL_TRIANGLES, it->vertexStart, it->vertexCount);
            //glPopMatrix();
    }
    //glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);

//    glDisableVertexAttribArray(m_tangentLoc);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}


void Mesh3DSGL::CalcTangents(const Vector3f* pVertices,
                             const Vector2f* pTexels,
                             Vector3f* pTangents,
                             Vector3f* pBitangents)
{
    for (unsigned int i = 0 ; i < m_vertexCount - 2 ; i++) {
        const Vector3f& P0 = pVertices[i];
        const Vector3f& P1 = pVertices[i + 1];
        const Vector3f& P2 = pVertices[i + 2];

        const Vector3f Edge1 = P1 - P0;
        const Vector3f Edge2 = P2 - P0;

        const Vector2f& UV0 = pTexels[i];
        const Vector2f& UV1 = pTexels[i + 1];
        const Vector2f& UV2 = pTexels[i + 2];

        const float s1 = UV1.x - UV0.x;
        const float s2 = UV2.x - UV0.x;
        const float t1 = UV1.y - UV0.y;
        const float t2 = UV2.y - UV0.y;

        const float f = 1.0f / (s1 * t2 - s2* t1);

        // calculate the tangent
        {
            Vector3f Tangent(f * (t2 * Edge1.x - t1 * Edge2.x) * -1.0,
                             f * (t2 * Edge1.y - t1 * Edge2.y) * -1.0,
                             f * (t2 * Edge1.z - t1 * Edge2.z) * -1.0);

            Tangent.Normalize();

            pTangents[i]     = Tangent;
            pTangents[i + 1] = Tangent;
            pTangents[i + 2] = Tangent;
        }

        // calculate the bitangent
        {
            Vector3f Bitangent(f * (-s2 * Edge1.x + s1 * Edge2.x),
                               f * (-s2 * Edge1.y + s1 * Edge2.y),
                               f * (-s2 * Edge1.z + s1 * Edge2.z));

            Bitangent.Normalize();

            pBitangents[i]     = Bitangent;
            pBitangents[i + 1] = Bitangent;
            pBitangents[i + 2] = Bitangent;
        }
    }
}

