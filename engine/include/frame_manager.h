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

#ifndef _FRAME_MANAGER_H
#define	_FRAME_MANAGER_H

#include "interfaces/lighting.h"
#include "interfaces/mesh.h"
#include "interfaces/camera.h"
#include "base_light.h"
#include "backend/GL/texture_tech_gl.h"
#include "backend/GL/bump_technique_gl.h"
#include "base_mesh.h"
#include "backend_factory.h"
#include "backend/GL/skybox_technique_gl.h"

#define MAX_LIGHTS 8

class FrameManager
{
public:
    FrameManager(MeshList& meshList, BackendFactory* pBackendFactory);
    ~FrameManager();

    void TurnOn(BasePointLight* pLight);
    void TurnOff(BasePointLight* pLight);

    void AddToFrame(IMesh* pMesh);
    void RemoveFromFrame(IMesh* pMesh);

    void SetCurrentCamera(ICamera* pCamera);
    void SetSkyBox(const ITexture* pSkyBox);

    void RenderFrame();

private:
    BasePointLight* m_pLights[MAX_LIGHTS];    
    MeshList& m_meshList;
    ICamera* m_pCurrentCamera;
    const ITexture* m_pSkyBoxTexture;
    BaseMesh* m_pSkyBoxMesh;
    BackendFactory* m_pBackendFactory;

    // techniques
    TextureTechGL m_textureTech;
    BumpMapTechGL m_bumpMapTech;
    SkyBoxTechGL m_skyBooxTech;
};

#endif	/* _FRAME_MANAGER_H */

