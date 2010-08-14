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

#ifndef _COLOSSUS_H
#define	_COLOSSUS_H

#include <string>

#include "interfaces/colossus_base.h"
#include "interfaces/lighting.h"
#include "interfaces/texture.h"
#include "interfaces/callbacks.h"
#include "backend_factory.h"
#include "mesh.h"

class IColossus
{
public:
    virtual void SetApplication(IColossusCallbacks* pApp) = 0;

    //
    // Lighing API
    //
    virtual ILight* CreateLight(LIGHT_TYPE LightType) = 0;
    virtual void DestroyLight(ILight* pLight) = 0;

    //
    // Mesh API
    //
    virtual IMesh* CreateMesh(const std::string& MeshName, const std::string& FileName) = 0;
    virtual void DestroyMesh(IMesh* pMesh) = 0;
    virtual IMesh* CreateMeshSphere(const std::string& MeshName,
                                    float Radius,
                                    unsigned int NumSlices,
                                    unsigned int NumStacks) = 0;
    virtual IMesh* CreateMeshBox(const std::string& MeshName) = 0;

    //
    // Texture API
    //
    virtual ITexture* CreateTexture(COLOSSUS_TEXTURE_TYPE TextureType) = 0;
    virtual void DestroyTexture(ITexture* pTexture) = 0;
    virtual void SetSkyBox(const ITexture* pTexture) = 0;

    //
    // Camera API
    //
    virtual ICamera* CreateCamera(int WindowWidth,
                                  int WindowHeight,
                                  const Vector3f& Pos,
                                  const Vector3f& Target,
                                  const Vector3f& Up) = 0;
    virtual ICamera* CreateCamera(int WindowWidth,
                                  int WindowHeight) = 0;

    virtual void DestroyCamera(ICamera* pCamera) = 0;

    virtual void SetCurrentCamera(ICamera* pCamera) = 0;

    virtual void RenderFrame() = 0;

    virtual void Run() = 0;
};


IColossus* ColossusInit(const ColossusCfg* pCfg);

void ColossusDestroy(IColossus* pColossus);

#endif	/* _COLOSSUS_H */

