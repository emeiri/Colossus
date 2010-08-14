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


#include <stdio.h>
#include "GLee.h"
#include <GL/glu.h>

#include "backend/GL/camera_gl.h"


CameraGL::CameraGL(int WindowWidth, int WindowHeight) : CameraBase(WindowWidth, WindowHeight)
{

}

CameraGL::CameraGL(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
    : CameraBase(WindowWidth, WindowHeight, Pos, Target, Up)
{

}

void CameraGL::Apply()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    printf("Camera: position "); m_Pos.Print(false); printf(" target "); m_Target.Print();

    gluLookAt(m_Pos.x, m_Pos.y, m_Pos.z,
              m_Target.x, m_Target.y, m_Target.z,
              m_Up.x, m_Up.y, m_Up.z);
}

