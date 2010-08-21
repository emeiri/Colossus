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

#ifndef _MESH_MD2_GL_H
#define	_MESH_MD2_GL_H

#include <list>
#include <lib3ds/file.h>

#include "interfaces/colossus_errors.h"
#include "interfaces/colossus_math.h"
#include "base_mesh_gl.h"
#include "texture_gl.h"

class MeshMD2GL : public BaseMeshGL
{
public:
    MeshMD2GL(FrameManager* pFrameManager, const std::string& Name);

    ~MeshMD2GL();

    ColossusErrors::COLOSSUS_ERROR Load(const std::string& pFilename);

    void Render();

private:

    Texture2DGL m_texture;
    GLuint m_meshList;
};


#endif	/* _MESH_2D_GL_H */

