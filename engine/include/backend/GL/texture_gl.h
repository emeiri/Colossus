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

#ifndef _TEXTURE_GL_H
#define	_TEXTURE_GL_H

#include "interfaces/texture.h"

#define ILUT_USE_OPENGL
#include <IL/ilut.h>

class BaseTextureGL : public ITexture
{
public:
    BaseTextureGL();
    
    ~BaseTextureGL();

    GLuint GetTextureHandle() const
    {
        return m_texName;
    }

protected:
    GLuint m_texName;
};

class Texture2DGL : public BaseTextureGL
{
public:
    Texture2DGL();

    ColossusErrors::COLOSSUS_ERROR Load2D(const std::string& FileName);

    ColossusErrors::COLOSSUS_ERROR LoadCubeMap(const std::string& FileNameTop,
                                               const std::string& FileNameBottom,
                                               const std::string& FileNameLeft,
                                               const std::string& FileNameRight,
                                               const std::string& FileNameFront,
                                               const std::string& FileNameBack);
};


class CubemapTextureGL : public BaseTextureGL
{
public:
    CubemapTextureGL();

    ~CubemapTextureGL();

    ColossusErrors::COLOSSUS_ERROR Load2D(const std::string& FileName);

    ColossusErrors::COLOSSUS_ERROR LoadCubeMap(const std::string& FileNameTop,
                                               const std::string& FileNameBottom,
                                               const std::string& FileNameLeft,
                                               const std::string& FileNameRight,
                                               const std::string& FileNameFront,
                                               const std::string& FileNameBack);
private:
    enum CubemapIndices {
        CUBEMAP_TOP,
        CUBEMAP_BOTTOM,
        CUBEMAP_LEFT,
        CUBEMAP_RIGHT,
        CUBEMAP_FRONT,
        CUBEMAP_BACK
    };

    ILuint m_imageNames[6];
};

#endif	/* _TEXTURE_GL_H */

