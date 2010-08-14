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


#ifndef _BASE_MESH_H_
#define _BASE_MESH_H_

#include <set>
#include "interfaces/mesh.h"
#include "interfaces/orientation.h"

class FrameManager;

class BaseMesh : public IMesh
{
public:
    BaseMesh(FrameManager* pFrameManager, const std::string& Name);

    void AddToFrame();

    void RemoveFromFrame();

    void SetBumpMap(ITexture* pBumpMap);
    ITexture* GetBumpMap() const;

    void SetColorMap(ITexture* pColorMap);
    ITexture* GetColorMap() const;

    Orientation& GetOrientation();

    const std::string& GetName() const;
    
    void SetScale(float Scale);
    float GetScale() const;

private:
    FrameManager* m_pFrameManager;
    std::string m_name;
    ITexture* m_pBumpMap;
    ITexture* m_pColorMap;
    Orientation m_orientation;
    float m_scale;
};

typedef std::set<IMesh*> MeshList;

#endif
