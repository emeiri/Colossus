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


#include "cubemap_tech.h"

CubeMapTech::CubeMapTech()
{
	if (!AddShaderFile("../../Colossus/shaders/cubemap.fs", GL_FRAGMENT_SHADER)) {
		throw new exception;
	}

	if (!AddShaderFile("../../Colossus/shaders/lighting_lib.fs", GL_FRAGMENT_SHADER)) {
		throw new exception;
	}

	if (!AddShaderFile("../../Colossus/shaders/cubemap.vs", GL_VERTEX_SHADER)) {
		throw new exception;
	}

	if (!Finalize()) {
		throw new exception;
	}

	m_texture = GetUniformLocation("SamplerCube");	
	glUniform1i(m_texture, 0);

	m_numLightsLoc = GetUniformLocation("gNumLights");
}


void CubeMapTech::SetNumLights(int NumLights)
{
	glUniform1i(m_numLightsLoc, NumLights);
}


