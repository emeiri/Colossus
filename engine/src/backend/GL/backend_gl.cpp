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
#include <GL/glut.h>

#include "backend/GL/backend_gl.h"
#include <IL/ilut.h>

bool InitGL(int WindowWidth, int WindowHeight)
{
    int argc = 1;
    const char* argv[1];
    argv[0] = "nofile";

    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(WindowWidth, WindowHeight);
//    glutGameModeString("800x600@32");
//    glutEnterGameMode();
    glutInitWindowPosition(100, 100);
    glutCreateWindow("a");

    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);

    InitCallbacksGL();


    return true;
}
