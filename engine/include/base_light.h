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

#ifndef _BASE_LIGHT_H
#define	_BASE_LIGHT_H

#include "interfaces/lighting.h"

class FrameManager;

class BasePointLight : public ILight
{
public:
    BasePointLight(FrameManager* pFrameManager);

    void SetPos(const Vector3f& Pos);
    void SetPos(float x, float y, float z);
    void SetAmbient(Vector3f& Ambient);
    void SetAmbient(float r, float g, float b);
    void SetDiffuse(Vector3f& Diffuse);
    void SetDiffuse(float r, float g, float b);
    void SetSpecular(Vector3f& Specular);
    void SetSpecular(float r, float g, float b);
    void SetAttenuation(float Const, float Linear, float Quad);
    void SetExponent(float Exponent);
    void SetDirection(float x, float y, float z);
    void SetDirection(const Vector3f& Dir);
    void SetCutoff(float Cutoff);

    void TurnOff();
    void TurnOn();

    virtual void Apply(unsigned int Index) = 0;

protected:
    FrameManager* m_pFrameManager;

    Vector4f m_pos;

    Vector3f m_ambient;
    Vector3f m_diffuse;
    Vector3f m_specular;

    float m_constAtten;
    float m_linearAtten;
    float m_quadAtten;

    float m_exponent;
};

class BaseSpotLight
{
public:
    BaseSpotLight();

protected:
    Vector4f m_dir;
    float m_cutoff;
};


#endif	/* _BASE_LIGHT_H */

