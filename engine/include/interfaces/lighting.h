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

#ifndef _LIGHTING_H
#define	_LIGHTING_H

#include "interfaces/colossus_math.h"

enum LIGHT_TYPE
{
    LIGHT_TYPE_DIRECTIONAL_LIGHT,
    LIGHT_TYPE_POINT_LIGHT,
    LIGHT_TYPE_SPOT_LIGHT
};

class ILight
{
public:
    ILight() {}
    
    virtual void SetPos(const Vector3f& Pos) = 0;
    virtual void SetPos(float x, float y, float z) = 0;
    virtual void SetAmbient(Vector3f& Ambient) = 0;
    virtual void SetAmbient(float r, float g, float b) = 0;
    virtual void SetDiffuse(Vector3f& Diffuse) = 0;
    virtual void SetDiffuse(float r, float g, float b) = 0;
    virtual void SetSpecular(Vector3f& Specular) = 0;
    virtual void SetSpecular(float r, float g, float b) = 0;
    virtual void SetAttenuation(float Const, float Linear, float Quad) = 0;
    virtual void SetExponent(float Exponent) = 0;
    virtual void SetDirection(float x, float y, float z) = 0;
    virtual void SetDirection(const Vector3f& Dir) = 0;
    virtual void SetCutoff(float Cutoff) = 0;

    virtual void TurnOff() = 0;
    virtual void TurnOn() = 0;
};


#endif	/* _LIGHTING_H */

