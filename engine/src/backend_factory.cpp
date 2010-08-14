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


#include <unistd.h>

#include "colossus_common.h"
#include "backend/GL/mesh_3ds_gl.h"
#include "backend_factory.h"
#include "interfaces/lighting.h"
#include "backend/GL/light_gl.h"
#include "backend/GL/texture_gl.h"
#include "backend/GL/camera_gl.h"
#include "backend/GL/mesh_sphere_gl.h"
#include "backend/GL/box_gl.h"


BackendFactory::BackendFactory()
{
    m_pFrameManager = NULL;
    m_backendType = BACKEND_TYPE_OPENGL;
    m_objectInventory.lights = 0;    
}


BackendFactory::~BackendFactory()
{
    assert(m_objectInventory.lights == 0);
}


void BackendFactory::SetFrameManager(FrameManager* pFrameManager)
{
    assert(!m_pFrameManager);
    m_pFrameManager = pFrameManager;
}


ILight* BackendFactory::CreateLight(LIGHT_TYPE LightType)
{
    ILight* pLight = NULL;

    switch(m_backendType)
    {
        case BACKEND_TYPE_OPENGL:
            pLight = CreateLightGL(LightType);
            break;

        default:
            assert(0);
    }

    if (pLight) {
        m_objectInventory.lights++;
    }

    return pLight;
}

void BackendFactory::DestroyLight(ILight* pLight)
{
    delete pLight;
    m_objectInventory.lights--;
}


ILight* BackendFactory::CreateLightGL(LIGHT_TYPE LightType)
{
    ILight* pLight = NULL;

    switch (LightType) {
        case LIGHT_TYPE_DIRECTIONAL_LIGHT:
            assert(0);
            break;

        case LIGHT_TYPE_POINT_LIGHT:
            pLight = new PointLightGL(m_pFrameManager);
            break;

        case LIGHT_TYPE_SPOT_LIGHT:
            pLight = new SpotLightGL(m_pFrameManager);
            break;

        default:
            assert(0);
    }

    return pLight;
}


ITexture* BackendFactory::CreateTexture(COLOSSUS_TEXTURE_TYPE TextureType)
{
    ITexture* pTexture = NULL;

    switch(m_backendType)
    {
        case BACKEND_TYPE_OPENGL:
            pTexture = CreateTextureGL(TextureType);
            break;

        default:
            assert(0);
    }

    return pTexture;
}

ITexture* BackendFactory::CreateTextureGL(COLOSSUS_TEXTURE_TYPE TextureType)
{
    ITexture* pTexture = NULL;

    switch (TextureType) {
        case COLOSSUS_TEXTURE_TYPE_2D:
            pTexture = new Texture2DGL();
            break;

        case COLOSSUS_TEXTURE_TYPE_CUBEMAP:
            pTexture = new CubemapTextureGL();
            break;

        default:
            assert(0);
    }

    return pTexture;
}


void BackendFactory::DestroyTexture(ITexture* pTexture)
{
    delete pTexture;
}


ICamera* BackendFactory::CreateCamera(int WindowWidth,
                                      int WindowHeight,
                                      const Vector3f& Pos,
                                      const Vector3f& Target,
                                      const Vector3f& Up)
{
    ICamera* pCamera = NULL;

    switch(m_backendType)
    {
        case BACKEND_TYPE_OPENGL:
            pCamera = new CameraGL(WindowWidth, WindowHeight, Pos, Target, Up);
            break;

        default:
            assert(0);
    }

    return pCamera;
}


ICamera* BackendFactory::CreateCamera(int WindowWidth, int WindowHeight)
{
    assert(0);
    return NULL;
}

void BackendFactory::DestroyCamera(ICamera* pCamera)
{
    delete pCamera;
}


BaseMesh* BackendFactory::CreateMesh(const std::string& MeshName, const std::string& FileName)
{
    BaseMesh* pMesh = NULL;

    if (m_backendType == BACKEND_TYPE_OPENGL) {
        if (FileName.substr(FileName.length() - 4) == ".3ds")
        {
            pMesh = new Mesh3DSGL(m_pFrameManager, MeshName);
            if (pMesh->Load(FileName) != ColossusErrors::NO_ERROR)
            {
                delete pMesh;
                pMesh = NULL;
            }
        }
        else
        {
            assert(0);
        }
    }
    else {
        assert(0);
    }

    return pMesh;
}

BaseMesh* BackendFactory::CreateMeshSphere(const std::string& MeshName,
                                        float Radius,
                                        unsigned int NumSlices,
                                        unsigned int NumStacks)
{
    BaseMesh* pRet = NULL;

    switch (m_backendType) {
        case BACKEND_TYPE_OPENGL:
            pRet = new MeshSphereGL(m_pFrameManager, MeshName, Radius, NumSlices, NumStacks);
            break;

        default:
            assert(0);
    }

    return pRet;
}

BaseMesh* BackendFactory::CreateMeshBox(const std::string& MeshName)
{
    BaseMesh* pRet = NULL;

    switch (m_backendType) {
        case BACKEND_TYPE_OPENGL:
            pRet = new BoxGL(m_pFrameManager, MeshName, 1.0f);
            break;

        default:
            assert(0);
    }

    return pRet;
}


void BackendFactory::DestroyMesh(BaseMesh* pMesh)
{
    assert(pMesh);
    delete pMesh;
}
