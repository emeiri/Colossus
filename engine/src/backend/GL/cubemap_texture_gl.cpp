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
#include "interfaces/colossus_errors.h"
#include "backend/GL/texture_gl.h"


CubemapTextureGL::CubemapTextureGL()
{
    ilGenImages(ARRAY_SIZE(m_imageNames), m_imageNames);
}

CubemapTextureGL::~CubemapTextureGL()
{
    ilDeleteImages(ARRAY_SIZE(m_imageNames), m_imageNames);
}

ColossusErrors::COLOSSUS_ERROR CubemapTextureGL::Load2D(const std::string& FileName)
{
    return ColossusErrors::UNSUPPORTED_OPERATION;
}

ColossusErrors::COLOSSUS_ERROR CubemapTextureGL::LoadCubeMap(const std::string& FileNameTop,
                                                             const std::string& FileNameBottom,
                                                             const std::string& FileNameLeft,
                                                             const std::string& FileNameRight,
                                                             const std::string& FileNameFront,
                                                             const std::string& FileNameBack)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texName);
    printf("Binding %d\n", m_texName);

    // Top
    ilBindImage(m_imageNames[CUBEMAP_TOP]);
    if (!ilLoadImage(FileNameTop.c_str())) {
        return ColossusErrors::FILE_NOT_FOUND;
    }

    printf("Loaded top '%s'\n", FileNameTop.c_str());

    // assumption: all images are of the same width/height
    const unsigned int ImageWidth = ilGetInteger(IL_IMAGE_WIDTH);
    const unsigned int ImageHeight = ilGetInteger(IL_IMAGE_HEIGHT);
    printf("Width %d Height %d BPP %d data size %d\n",
            ImageWidth, ImageHeight, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_SIZE_OF_DATA));

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

    // Bottom
    ilBindImage(m_imageNames[CUBEMAP_BOTTOM]);
    if (!ilLoadImage(FileNameBottom.c_str())) {
        return ColossusErrors::FILE_NOT_FOUND;
    }
    printf("Loaded bottom '%s'\n", FileNameBottom.c_str());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

    // Left
    ilBindImage(m_imageNames[CUBEMAP_LEFT]);
    if (!ilLoadImage(FileNameLeft.c_str())) {
        return ColossusErrors::FILE_NOT_FOUND;
    }
    printf("Loaded left '%s'\n", FileNameLeft.c_str());

    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

    printf("Loading right...\n");
    // Right
    ilBindImage(m_imageNames[CUBEMAP_RIGHT]);
    if (!ilLoadImage(FileNameRight.c_str())) {
        return ColossusErrors::FILE_NOT_FOUND;
    }
    printf("Loaded right '%s'\n", FileNameRight.c_str());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

    // Front
    ilBindImage(m_imageNames[CUBEMAP_FRONT]);
    if (!ilLoadImage(FileNameFront.c_str())) {
        return ColossusErrors::FILE_NOT_FOUND;
    }
    printf("Loaded front '%s'\n", FileNameFront.c_str());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

    // Back
    ilBindImage(m_imageNames[CUBEMAP_BACK]);
    if (!ilLoadImage(FileNameBack.c_str())) {
        return ColossusErrors::FILE_NOT_FOUND;
    }
    printf("Loaded back '%s'\n", FileNameBack.c_str());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

    return ColossusErrors::NO_ERROR;
}


