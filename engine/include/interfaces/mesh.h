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

#ifndef _MESH_H
#define	_MESH_H

#include <string>

#include "colossus_errors.h"
#include "texture.h"
#include "orientation.h"

class IMesh
{
public:
    IMesh(const std::string& Name) {}

    virtual ColossusErrors::COLOSSUS_ERROR Load(const std::string& FileName) = 0;

    virtual void Render() = 0;

    virtual void AddToFrame() = 0;

    virtual void RemoveFromFrame() = 0;

    virtual void SetBumpMap(ITexture* pBumpMap) = 0;
    virtual ITexture* GetBumpMap() const = 0;

    virtual void SetColorMap(ITexture* pColorMap) = 0;
    virtual ITexture* GetColorMap() const = 0;

    virtual void SetScale(float Scale) = 0;

    virtual Orientation& GetOrientation() = 0;
};


#endif	/* _MESH_H */

