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
#include "GLee.h"
#include <GL/glut.h>
#include "colossus_common.h"
#include "frame_manager.h"
#include "base_mesh.h"
#include "backend/GL/base_mesh_gl.h"
#include "interfaces/camera.h"
#include "base_camera.h"

FrameManager::FrameManager(MeshList& meshList, BackendFactory* pBackendFactory) :
    m_meshList(meshList)
{
    m_pBackendFactory = pBackendFactory;
    m_pCurrentCamera = NULL;
    memset(m_pLights, 0, sizeof(m_pLights));
    m_pSkyBoxTexture = NULL;
    m_pSkyBoxMesh = m_pBackendFactory->CreateMeshBox("SkyBox");
}

FrameManager::~FrameManager()
{
    m_pBackendFactory->DestroyMesh(m_pSkyBoxMesh);
}


void FrameManager::TurnOn(BasePointLight* pLight)
{
    for (unsigned int i = 0 ; i < ARRAY_SIZE(m_pLights) ; i++) {
        // nothing to do if light already turned on
        if (m_pLights[i] == pLight)
            break;

        // find the first empty slot
        if (!m_pLights[i]) {
            m_pLights[i] = pLight;
            return;
        }
    }

    // should never get here - means we overflowed the array
    assert(0);
}

void FrameManager::TurnOff(BasePointLight* pLight)
{
    unsigned int i = 0;

    // find the light to remove
    while (i < ARRAY_SIZE(m_pLights)) {
        if (m_pLights[i] == pLight) {
            m_pLights[i] = NULL; // in case this is the last light...
            break;
        }

        i++;
    }

    assert(i < ARRAY_SIZE(m_pLights));

    unsigned int j = ARRAY_SIZE(m_pLights) - 1;

    // find the last slot and replace it with the one removed
    while (j > i) {
        if (m_pLights[j]) {
            m_pLights[i] = m_pLights[j];
            m_pLights[j] = NULL;
            break;
        }

        j--;
    }

    assert(j != i);
}

void FrameManager::AddToFrame(IMesh* pMesh)
{
    if (m_meshList.find(pMesh) == m_meshList.end()) {
        m_meshList.insert(pMesh);
    }
}

void FrameManager::RemoveFromFrame(IMesh* pMesh)
{
    m_meshList.erase(pMesh);
}

void FrameManager::RenderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_pCurrentCamera) {
        m_pCurrentCamera->OnRender();
    }

    unsigned int i = 0;
    
    for ( ; i < ARRAY_SIZE(m_pLights) ; i++) {
        if (!m_pLights[i])
            break;

        m_pLights[i]->Apply(i);
    }    

    if (m_pSkyBoxTexture) {
        m_skyBooxTech.Enable();
        m_pSkyBoxMesh->SetScale(1000.0f);
        m_pSkyBoxMesh->GetOrientation().SetPos(((CameraBase*)m_pCurrentCamera)->GetPos());
        m_skyBooxTech.RenderMesh((BaseMeshGL*)m_pSkyBoxMesh);
    }

    for (MeshList::iterator it = m_meshList.begin() ; it != m_meshList.end() ; it++) {
        IMesh* pMesh = *it;
        BaseMeshGL* pMeshGL = dynamic_cast<BaseMeshGL*>(pMesh);
        assert(pMeshGL);
        BaseTechniqueGL* pTech = NULL;        

        if (pMeshGL->GetBumpMap()) {
          //  printf("Drawing '%s' using bump map technique\n", ((BaseMesh*)pMesh)->GetName().c_str());
            pTech = &m_bumpMapTech;
            pTech->Enable();
            m_bumpMapTech.SetNumLights(i);
        }
        else {
          //  printf("Drawing '%s' using texture map technique\n", ((BaseMesh*)pMesh)->GetName().c_str());
            pTech = &m_textureTech;
            pTech->Enable();
            m_textureTech.SetNumLights(i);
        }
        
        pTech->RenderMesh(pMeshGL);
    }

    glutSwapBuffers();
}


void FrameManager::SetCurrentCamera(ICamera* pCamera)
{
    m_pCurrentCamera = pCamera;
}

void FrameManager::SetSkyBox(const ITexture* pSkyBox)
{
    m_pSkyBoxTexture = pSkyBox;
    m_skyBooxTech.SetSkyBox((CubemapTextureGL*)pSkyBox);
}