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
#include "base_light.h"
#include "frame_manager.h"

BasePointLight::BasePointLight(FrameManager* pFrameManager)
{
    m_pFrameManager = pFrameManager;
    m_pos = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
    m_ambient = Vector3f(0.0f, 0.0f, 0.0f);
    m_diffuse = Vector3f(0.0f, 0.0f, 0.0f);
    m_specular = Vector3f(0.0f, 0.0f, 0.0f);
    m_constAtten = 0.0f;
    m_linearAtten = 0.0f;
    m_quadAtten = 0.0f;
    m_exponent = 0.0f;
}


void BasePointLight::SetPos(const Vector3f& Pos)
{
	m_pos.x = Pos.x;
	m_pos.y = Pos.y;
	m_pos.z = Pos.z;
	//m_pos.w = 1.0f;
}

void BasePointLight::SetPos(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}


void BasePointLight::SetAmbient(Vector3f& Ambient)
{
	m_ambient = Ambient;
}

void BasePointLight::SetAmbient(float r, float g, float b)
{
	m_ambient.x = r;
	m_ambient.y = g;
	m_ambient.z = b;
}

void BasePointLight::SetDiffuse(Vector3f& Diffuse)
{
	m_diffuse = Diffuse;
}

void BasePointLight::SetDiffuse(float r, float g, float b)
{
	m_diffuse.x = r;
	m_diffuse.y = g;
	m_diffuse.z = b;
}


void BasePointLight::SetSpecular(Vector3f& Specular)
{
	m_specular = Specular;
}

void BasePointLight::SetSpecular(float r, float g, float b)
{
	m_specular.x = r;
	m_specular.y = g;
	m_specular.z = b;
}

void BasePointLight::SetAttenuation(float Const, float Linear, float Quad)
{
	m_constAtten = Const;
	m_linearAtten = Linear;
	m_quadAtten = Quad;
}

void BasePointLight::SetExponent(float Exponent)
{
	m_exponent = Exponent;
}

void BasePointLight::TurnOff()
{
    m_pFrameManager->TurnOff(this);
}


void BasePointLight::TurnOn()
{
    m_pFrameManager->TurnOn(this);
}


void BasePointLight::SetDirection(float x, float y, float z)
{
    assert(0);
}

void BasePointLight::SetDirection(const Vector3f& Dir)
{
    assert(0);
}


void BasePointLight::SetCutoff(float Cutoff)
{
    assert(0);
}

///////////////////////////////////////////////////////////////////////////////////////

BaseSpotLight::BaseSpotLight()
{
	m_dir = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
	m_cutoff = 0.0f;
}



