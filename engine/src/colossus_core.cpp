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
#include "GLee.h"
#include <GL/glut.h>
#include "colossus_common.h"
#include "colossus_core.h"
#include "base_light.h"
#include "backend/GL/backend_gl.h"

IColossus* ColossusCore::m_pInstance = NULL;

ColossusCore::ColossusCore(const ColossusCfg* pCfg) : m_physicsSubsystem(m_meshList)
{
    InitGL(pCfg->WindowWidth, pCfg->WindowHeight);
    m_pBackendFactory = new BackendFactory();
    m_pFrameManager = new FrameManager(m_meshList, m_pBackendFactory);
    m_pBackendFactory->SetFrameManager(m_pFrameManager);
}


ColossusCore::~ColossusCore()
{
    delete m_pBackendFactory;
    delete m_pFrameManager;
}


IColossus* ColossusCore::GetInstance(const ColossusCfg* pCfg)
{
    if (m_pInstance) {
        assert(0);
        return m_pInstance;
    }
    else {
        m_pInstance = new ColossusCore(pCfg);
        return m_pInstance;
    }
}


void ColossusCore::ReleaseInstance(IColossus* pColossus)
{
    assert(pColossus == m_pInstance);
    delete pColossus;
    m_pInstance = NULL;
}


void ColossusCore::SetApplication(IColossusCallbacks* pApp)
{
    SetApplicationGL(pApp);
}

ILight* ColossusCore::CreateLight(LIGHT_TYPE LightType)
{
    return m_pBackendFactory->CreateLight(LightType);
}


void ColossusCore::DestroyLight(ILight* pLight)
{
    m_pBackendFactory->DestroyLight(pLight);
}

IMesh* ColossusCore::CreateMesh(const std::string& MeshName, const std::string& FileName)
{
    return m_pBackendFactory->CreateMesh(MeshName, FileName);
}


IMesh* ColossusCore::CreateMeshSphere(const std::string& MeshName,
                                      float Radius,
                                      unsigned int NumSlices,
                                      unsigned int NumStacks)
{
    return m_pBackendFactory->CreateMeshSphere(MeshName, Radius, NumSlices, NumStacks);
}

IMesh* ColossusCore::CreateMeshBox(const std::string& MeshName)
{
    return m_pBackendFactory->CreateMeshBox(MeshName);
}

void ColossusCore::DestroyMesh(IMesh* pMesh)
{
    m_pBackendFactory->DestroyMesh((BaseMesh*)pMesh);
}


ITexture* ColossusCore::CreateTexture(COLOSSUS_TEXTURE_TYPE TextureType)
{
    return m_pBackendFactory->CreateTexture(TextureType);
}

void ColossusCore::DestroyTexture(ITexture* pTexture)
{
    m_pBackendFactory->DestroyTexture(pTexture);
}


void ColossusCore::SetSkyBox(const ITexture* pSkyBox)
{
    m_pFrameManager->SetSkyBox(pSkyBox);
}

ICamera* ColossusCore::CreateCamera(int WindowWidth,
                          int WindowHeight,
                          const Vector3f& Pos,
                          const Vector3f& Target,
                          const Vector3f& Up)
{
    return m_pBackendFactory->CreateCamera(WindowWidth, WindowHeight, Pos,
                                           Target, Up);
}


ICamera* ColossusCore::CreateCamera(int WindowWidth, int WindowHeight)
{
    return m_pBackendFactory->CreateCamera(WindowWidth, WindowHeight);
}


void ColossusCore::DestroyCamera(ICamera* pCamera)
{
    m_pBackendFactory->DestroyCamera(pCamera);
}


void ColossusCore::RenderFrame()
{
    m_physicsSubsystem.RenderFrame();
    m_pFrameManager->RenderFrame();
}

void ColossusCore::SetCurrentCamera(ICamera* pCamera)
{
    m_pFrameManager->SetCurrentCamera(pCamera);
}

void ColossusCore::Run()
{
    glutMainLoop();
}

IColossus* ColossusInit(const ColossusCfg* pCfg)
{
    return ColossusCore::GetInstance(pCfg);
}

void ColossusDestroy(IColossus* pColossus)
{
    ColossusCore::ReleaseInstance(pColossus);
}

