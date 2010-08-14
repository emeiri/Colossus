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

#ifndef _BUMPMAP_TECHNIQUE_H
#define	_BUMPMAP_TECHNIQUE_H

#include "base_technique_gl.h"
#include "backend/GL/texture_gl.h"

class BumpMapTechGL : public BaseTechniqueGL
{
public:
    BumpMapTechGL();

    void SetNumLights(float NumLights);

    void RenderMeshInternal(BaseMeshGL* pMesh);

private:
    void SetColorMap(Texture2DGL* pTexture);
    void SetBumpMap(Texture2DGL* pBumpMap);

    GLuint m_colorMapLoc;
    GLuint m_bumpMapLoc;
    GLuint m_numLightsLoc;
    GLuint m_tangentLoc;
};


#endif	/* _BUMPMAP_TECHNIQUE_H */

