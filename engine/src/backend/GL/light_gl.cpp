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
#include "backend/GL/light_gl.h"
#include "frame_manager.h"

static GLuint GetGLLightIndex(unsigned int Index)
{
    GLuint LightIndex = 0;

    switch (Index) {
        case 0:
            LightIndex = GL_LIGHT0;
            break;

        case 1:
            LightIndex = GL_LIGHT1;
            break;

        case 2:
            LightIndex = GL_LIGHT2;
            break;

        case 3:
            LightIndex = GL_LIGHT3;
            break;

        case 4:
            LightIndex = GL_LIGHT4;
            break;

        case 5:
            LightIndex = GL_LIGHT5;
            break;

        case 6:
            LightIndex = GL_LIGHT6;
            break;

        case 7:
            LightIndex = GL_LIGHT7;
            break;

        default:
            assert(0);
    }

    return LightIndex;
}


PointLightGL::PointLightGL(FrameManager* pFrameManager) : BasePointLight(pFrameManager)
{
}


void PointLightGL::Apply(unsigned int Index)
{
    GLuint LightIndex = GetGLLightIndex(Index);
    
    glEnable(LightIndex);
    glLightfv(LightIndex, GL_POSITION, m_pos);
    glLightfv(LightIndex, GL_AMBIENT, m_ambient);
    glLightfv(LightIndex, GL_DIFFUSE, m_diffuse);
    glLightfv(LightIndex, GL_SPECULAR, m_specular);
    glLightfv(LightIndex, GL_CONSTANT_ATTENUATION, &m_constAtten);
    glLightfv(LightIndex, GL_LINEAR_ATTENUATION, &m_linearAtten);
    glLightfv(LightIndex, GL_QUADRATIC_ATTENUATION, &m_quadAtten);
    GLfloat CutoffValue = 180.0f;
    glLightfv(LightIndex, GL_SPOT_CUTOFF, &CutoffValue);
    glLightfv(LightIndex, GL_SPOT_EXPONENT, &m_exponent);
}


///////////////////////////////////////////////////////////////////////////////////////

SpotLightGL::SpotLightGL(FrameManager* pFrameManager) : PointLightGL(pFrameManager)
{
}


void SpotLightGL::Apply(unsigned int Index)
{
    PointLightGL::Apply(Index);

    GLuint LightIndex = GetGLLightIndex(Index);
    
    glLightfv(LightIndex, GL_SPOT_CUTOFF, &m_cutoff);
    glLightfv(LightIndex, GL_SPOT_DIRECTION, m_dir);
}

void SpotLightGL::SetDirection(float x, float y, float z)
{
	m_dir.x = x;
	m_dir.y = y;
	m_dir.z = z;
}

void SpotLightGL::SetDirection(const Vector3f& Dir)
{
    m_dir.x = Dir.x;
    m_dir.y = Dir.y;
    m_dir.z = Dir.z;
}


void SpotLightGL::SetCutoff(float Cutoff)
{
	m_cutoff = Cutoff;
}
