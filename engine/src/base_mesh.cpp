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


#include "base_mesh.h"
#include "frame_manager.h"

BaseMesh::BaseMesh(FrameManager* pFrameManager, const std::string& Name) 
    : IMesh(Name)
{
    m_pFrameManager = pFrameManager;
    m_name          = Name;
    m_pBumpMap      = NULL;
    m_pColorMap     = NULL;
    m_scale         = 1.0f;
}


void BaseMesh::AddToFrame()
{
    m_pFrameManager->AddToFrame(this);
}

void BaseMesh::RemoveFromFrame()
{
    m_pFrameManager->RemoveFromFrame(this);
}

void BaseMesh::SetBumpMap(ITexture* pBumpMap)
{
    m_pBumpMap = pBumpMap;
}

ITexture* BaseMesh::GetBumpMap() const
{
    return m_pBumpMap;
}

void BaseMesh::SetColorMap(ITexture* pColorMap)
{
    m_pColorMap = pColorMap;
}

ITexture* BaseMesh::GetColorMap() const
{
    return m_pColorMap;
}

Orientation& BaseMesh::GetOrientation()
{
    return m_orientation;
}

const std::string& BaseMesh::GetName() const
{
    return m_name;
}

void BaseMesh::SetScale(float Scale)
{
    m_scale = Scale;
}

float BaseMesh::GetScale() const
{
    return m_scale;
}