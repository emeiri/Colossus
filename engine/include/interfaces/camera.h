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

#ifndef _CAMERA_H
#define	_CAMERA_H

#include "interfaces/colossus_math.h"

class ICamera
{
public:

    ICamera(int WindowWidth, int WindowHeight) {}

    ICamera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

    virtual void SetVelocity(float Velocity) = 0;

    virtual void Move(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up) = 0;

    virtual void Apply() = 0;

    virtual bool OnKeyboard(int Key, int x, int y) = 0;

    virtual void OnPassiveMouseMov(int x, int y) = 0;

    virtual void OnRender() = 0;
};


#endif	/* _CAMERA_H */

