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


#include "colossus_common.h"
#include "backend/GL/mesh_md2_gl.h"


MeshMD2GL::MeshMD2GL(FrameManager* pFrameManager, const std::string& Name) : BaseMeshGL(pFrameManager, Name)
{
}

MeshMD2GL::~MeshMD2GL()
{

}


ColossusErrors::COLOSSUS_ERROR MeshMD2GL::Load(const std::string& pFilename)
{
    
}