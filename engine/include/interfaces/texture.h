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

#ifndef _TEXTURE_H
#define	_TEXTURE_H

#include <string>
#include "colossus_errors.h"

enum COLOSSUS_TEXTURE_TYPE
{
    COLOSSUS_TEXTURE_TYPE_2D,
    COLOSSUS_TEXTURE_TYPE_CUBEMAP
};

class ITexture
{
public:
    ITexture() {}

    virtual ColossusErrors::COLOSSUS_ERROR Load2D(const std::string& FileName) = 0;

    virtual ColossusErrors::COLOSSUS_ERROR LoadCubeMap(const std::string& FileNameTop,
                                                const std::string& FileNameBottom,
                                                const std::string& FileNameLeft,
                                                const std::string& FileNameRight,
                                                const std::string& FileNameFront,
                                                const std::string& FileNameBack) = 0;
};


#endif	/* _TEXTURE_H */

