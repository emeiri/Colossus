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


#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "base_light.h"

class FrameManager;

class PointLightGL : public BasePointLight
{
public:
    PointLightGL(FrameManager* pFrameManager);

    void Apply(unsigned int Index);
};

class SpotLightGL : public BaseSpotLight, public PointLightGL
{
public:
    SpotLightGL(FrameManager* pFrameManager);

    void SetDirection(float x, float y, float z);

    void SetDirection(const Vector3f& Dir);

    void SetCutoff(float Cutoff);

    void Apply(unsigned int Index);
};

#endif
