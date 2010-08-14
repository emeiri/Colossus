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

#ifndef _COLOSSUS_CORE_H
#define	_COLOSSUS_CORE_H

#include "interfaces/colossus.h"
#include "frame_manager.h"
#include "physics_subsystem.h"

class ColossusCore : public IColossus
{
public:
    static IColossus* GetInstance(const ColossusCfg* pCfg);
    static void ReleaseInstance(IColossus* pColossus);

    void SetApplication(IColossusCallbacks* pApp);

    ILight* CreateLight(LIGHT_TYPE LightType);
    void DestroyLight(ILight* pLight);

    IMesh* CreateMesh(const std::string& MeshName, const std::string& FileName);
    IMesh* CreateMeshSphere(const std::string& MeshName,
                            float Radius,
                            unsigned int NumSlices,
                            unsigned int NumStacks);
    IMesh* CreateMeshBox(const std::string& MeshName);

    void DestroyMesh(IMesh* pMesh);

    ITexture* CreateTexture(COLOSSUS_TEXTURE_TYPE TextureType);
    void DestroyTexture(ITexture* pTexture);
    void SetSkyBox(const ITexture* pTexture);

    ICamera* CreateCamera(int WindowWidth,
                          int WindowHeight,
                          const Vector3f& Pos,
                          const Vector3f& Target,
                          const Vector3f& Up);
    ICamera* CreateCamera(int WindowWidth,
                          int WindowHeight);
    void DestroyCamera(ICamera* pCamera);

    void SetCurrentCamera(ICamera* pCamera);

    void RenderFrame();

    void Run();

private:
    ColossusCore(const ColossusCfg* pCfg);
    ~ColossusCore();
    static IColossus* m_pInstance;

    MeshList m_meshList;
    BackendFactory* m_pBackendFactory;
    FrameManager* m_pFrameManager;
    PhysicsSubsystem m_physicsSubsystem;
};


#endif	/* _COLOSSUS_CORE_H */

