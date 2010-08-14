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


#ifndef _BOX_H_
#define _BOX_H_

#include <string>
#include "GLee.h"
#include "backend/GL/base_mesh_gl.h"


class BoxGL : public BaseMeshGL
{
public:
	BoxGL(FrameManager* pFrameManager, const std::string& Name, float Scale);

        ColossusErrors::COLOSSUS_ERROR Load(const std::string& FileName);

	void Render();

private:
	GLuint m_vertexVBO;
	GLuint m_indexVBO;
};

#endif
