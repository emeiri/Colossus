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

#ifndef _BACKEND_FACTORY_H
#define	_BACKEND_FACTORY_H

#include "interfaces/colossus_base.h"
#include "interfaces/lighting.h"
#include "interfaces/texture.h"
#include "interfaces/camera.h"
#include "base_mesh.h"

enum BACKEND_TYPE
{
    BACKEND_TYPE_OPENGL,
    BACKEND_TYPE_DX10,
    BACKEND_TYPE_DX11
};

class BackendFactory
{
public:
    BackendFactory();
    ~BackendFactory();

    void SetFrameManager(FrameManager* pFrameManager);
    
    ILight* CreateLight(LIGHT_TYPE LightType);
    void DestroyLight(ILight* pLight);

    ITexture* CreateTexture(COLOSSUS_TEXTURE_TYPE TextureType);
    void DestroyTexture(ITexture* pTexture);

    ICamera* CreateCamera(int WindowWidth,
                          int WindowHeight,
                          const Vector3f& Pos,
                          const Vector3f& Target,
                          const Vector3f& Up);
    ICamera* CreateCamera(int WindowWidth,
                          int WindowHeight);
    void DestroyCamera(ICamera* pCamera);

    BaseMesh* CreateMesh(const std::string& MeshName, const std::string& FileName);
    BaseMesh* CreateMeshSphere(const std::string& MeshName,
                            float Radius,
                            unsigned int NumSlices,
                            unsigned int NumStacks);
    BaseMesh* CreateMeshBox(const std::string& MeshName);

    void DestroyMesh(BaseMesh* pMesh);

private:
    ILight* CreateLightGL(LIGHT_TYPE LightType);
    ITexture* CreateTextureGL(COLOSSUS_TEXTURE_TYPE TextureType);

    BACKEND_TYPE m_backendType;
    FrameManager* m_pFrameManager;

    struct {
        unsigned int lights;
    } m_objectInventory;

};

#endif	/* _BACKEND_FACTORY_H */

