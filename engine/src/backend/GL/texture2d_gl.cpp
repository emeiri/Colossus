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
#include "backend/GL/texture_gl.h"

#include <IL/ilut.h>


Texture2DGL::Texture2DGL()
{

}


ColossusErrors::COLOSSUS_ERROR Texture2DGL::Load2D(const std::string& FileName)
{
    /*ILuint f;
    ilGenImages(1, &f);
    ilBindImage(f);
    ilLoadImage((char*)FileName.c_str());
     m_texName = ilutGLBindTexImage();*/
    m_texName = ilutGLLoadImage((char*)FileName.c_str());
    if (m_texName == 0) {
        printf("Unable to load '%s'\n", FileName.c_str());
        assert(0);
        return ColossusErrors::FILE_NOT_FOUND;
    }
    glBindTexture(GL_TEXTURE_2D, m_texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    return ColossusErrors::NO_ERROR;
}

ColossusErrors::COLOSSUS_ERROR Texture2DGL::LoadCubeMap(const std::string& FileNameTop,
                                                        const std::string& FileNameBottom,
                                                        const std::string& FileNameLeft,
                                                        const std::string& FileNameRight,
                                                        const std::string& FileNameFront,
                                                        const std::string& FileNameBack)
{
    return ColossusErrors::UNSUPPORTED_OPERATION;
}


