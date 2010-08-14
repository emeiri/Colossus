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


#ifndef _TEXTURE_TECH_H_
#define _TEXTURE_TECH_H_

#include "base_technique_gl.h"
#include "texture_gl.h"

class TextureTechGL : public BaseTechniqueGL
{
public:
	TextureTechGL();

	void SetNumLights(float NumLights);        

        void RenderMeshInternal(BaseMeshGL* pMesh);

private:
        void SetColorMap(Texture2DGL* pColorMap);

	GLuint m_texture;
	GLuint m_numLightsLoc;
};


#endif
