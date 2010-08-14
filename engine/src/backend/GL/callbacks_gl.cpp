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


#include <unistd.h>
#include "GLee.h"
#include <GL/glut.h>
#include "interfaces/callbacks.h"

static IColossusCallbacks* g3DApp = NULL;

static void RenderScene()
{
    g3DApp->OnRender();
}

static void ChangeSize(GLsizei w, GLsizei h)
{
	g3DApp->OnChangeSize(w, h);
}

static void TimerFunc(int Value)
{
	g3DApp->OnTimer(Value);
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunc, 0);
}

static void SpecialKeys(int Key, int x, int y)
{
	g3DApp->OnSpecialKeys(Key, x ,y);
}

static void Keyboard(unsigned char Key, int x, int y)
{
	g3DApp->OnKeyboard(Key, x, y);
}

static void PassiveMouseMov(int x, int y)
{
	g3DApp->OnPassiveMouseMov(x, y);
}

static void MouseMov(int x, int y)
{
	g3DApp->OnMouseMov(x, y);
}

static void Idle()
{
    glutPostRedisplay();
}

void InitCallbacksGL()
{	
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(10, TimerFunc, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeys);
    glutPassiveMotionFunc(PassiveMouseMov);
    glutMotionFunc(MouseMov);
    glutIdleFunc(Idle);
}

void SetApplicationGL(IColossusCallbacks* pApp)
{
    g3DApp = pApp;
}
