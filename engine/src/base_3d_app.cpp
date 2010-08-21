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
#include <stdlib.h>

#include "GLee.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include "base_3d_app.h"

Base3DApplication::Base3DApplication(int WindowWidth, int WindowHeight)
{
    struct ColossusCfg Cfg;
    Cfg.WindowHeight = WindowHeight;
    Cfg.WindowWidth = WindowWidth;
    m_pColossus = ColossusInit(&Cfg);
    
    SetupRenderState();

    m_pColossus->SetApplication(this);
}

Base3DApplication::~Base3DApplication()
{
    ColossusDestroy(m_pColossus);
}

void Base3DApplication::Run()
{
    m_pColossus->Run();
}

void Base3DApplication::OnChangeSize(GLsizei w, GLsizei h)
{
    if (h == 0) {
        h = 1;
    }

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat AspectRatio = (GLfloat)w / (GLfloat)h;

    gluPerspective(80.0f, AspectRatio, 0.1f, 1000.0f); 
}

void Base3DApplication::OnTimer(int Value)
{
}

void Base3DApplication::OnSpecialKeys(int Key, int x, int y)
{    

}

void Base3DApplication::OnKeyboard(unsigned char Key, int x, int y)
{
    switch (Key) {
    case 27:
            exit(0);

    case 'f':
            glutFullScreen();
            break;
    }
}


void Base3DApplication::OnPassiveMouseMov(int x, int y)
{
}

void Base3DApplication::OnMouseMov(int x, int y)
{
}

void Base3DApplication::OnRender()
{
    UpdateFrame();

    m_pColossus->RenderFrame();
}

void Base3DApplication::SetupRenderState()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_SMOOTH);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);
}

