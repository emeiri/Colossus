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
#include <stdio.h>
#include "backend/GL/skybox_technique_gl.h"


static const char* pVS = "                              \n\
// vectors required by the fragment shader              \n\
varying vec3 PosL;                                      \n\
                                                        \n\
                                                        \n\
void main()                                             \n\
{                                                       \n\
    vec4 PosV = ftransform();                           \n\
    gl_Position = PosV.xyww;                            \n\
	PosL = gl_Vertex.xyz;                               \n\
}";


static const char* pFS = "                                                    \n\
varying vec3 PosL;                                                            \n\
                                                                              \n\
uniform samplerCube SkyBox;                                                   \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    vec4 Texel = textureCube(SkyBox, PosL);                                   \n\
    gl_FragColor = Texel;                                                     \n\
}";

SkyBoxTechGL::SkyBoxTechGL()
{
    if (!AddShaderText(pFS, GL_FRAGMENT_SHADER)) {
        throw new exception;
    }

    if (!AddShaderText(pVS, GL_VERTEX_SHADER)) {
        throw new exception;
    }

    if (!Finalize()) {
        throw new exception;
    }

    m_skyBoxLoc = GetUniformLocation("SkyBox");
    assert(m_skyBoxLoc != -1);
}


void SkyBoxTechGL::RenderMeshInternal(BaseMeshGL* pMesh)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_pSkyBox->GetTextureHandle());
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glUniform1i(m_skyBoxLoc, 0);
}