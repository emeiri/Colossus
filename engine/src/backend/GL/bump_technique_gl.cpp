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
#include <stdio.h>
#include "backend/GL/bump_technique_gl.h"

static const char* pVS = "                                                  \n\
// vectors required by the fragment shader                                  \n\
attribute vec3 Tangent;                                                     \n\
                                                                            \n\
varying vec3 NormalV;                                                       \n\
varying vec3 TangentV;                                                      \n\
varying vec3 PosV;                                                          \n\
                                                                            \n\
                                                                            \n\
void main()                                                                 \n\
{                                                                           \n\
	gl_Position = ftransform();                                             \n\
	gl_TexCoord[0] = gl_MultiTexCoord0;                                     \n\
                                                                            \n\
	NormalV    = (gl_NormalMatrix * gl_Normal).xyz;                         \n\
    TangentV   = (gl_NormalMatrix * Tangent).xyz;                           \n\
	PosV       = (gl_ModelViewMatrix * gl_Vertex).xyz;                      \n\
}";


static const char* pFS = "                                                  \n\
uniform int gNumLights;                                                     \n\
                                                                            \n\
varying vec3 NormalV;                                                       \n\
varying vec3 TangentV;                                                      \n\
varying vec3 PosV;                                                          \n\
                                                                            \n\
uniform sampler2D ColorMap;                                                 \n\
uniform sampler2D BumpMap;                                                  \n\
vec4 GetLightIntensity(int Index, vec3 PosV, vec3 NormalV);                 \n\
                                                                            \n\
void main()                                                                             \n\
{                                                                                       \n\
    NormalV = normalize(NormalV);                                                       \n\
    TangentV = normalize(TangentV);                                                     \n\
    vec3 BinormalV = cross(NormalV, TangentV);                                          \n\
    vec3 VertexToLight;                                                                 \n\
    vec3 t = gl_LightSource[0].position - PosV;                                         \n\
                                                                                        \n\
    vec3 Normal = texture2D(BumpMap, gl_TexCoord[0].st).xyz;                            \n\
    Normal = 2.0 * (Normal) - vec3(1.0, 1.0, 1.0);                                      \n\
    Normal.x = Normal.x * TangentV.x + Normal.y * BinormalV.x + Normal.z * NormalV.x;   \n\
    Normal.y = Normal.x * TangentV.y + Normal.y * BinormalV.y + Normal.z * NormalV.y;   \n\
    Normal.z = Normal.x * TangentV.z + Normal.y * BinormalV.z + Normal.z * NormalV.z;   \n\
                                                                                        \n\
    vec4 Texel = texture2D(ColorMap, gl_TexCoord[0].st);                                \n\
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);                                            \n\
                                                                                        \n\
    for (int i = 0 ; i < gNumLights ; i++)                                              \n\
    {                                                                                   \n\
        gl_FragColor += Texel * GetLightIntensity(i, PosV, Normal);                     \n\
    }                                                                                   \n\
}";


static const char* pLightingLib = "                                                     \n\
vec4 GetDirectionalLightIntensity(int Index, vec3 PosV, vec3 Normal)                    \n\
{                                                                                       \n\
	// should be simply the position                                                    \n\
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;                    \n\
	VertexToLightV = normalize(VertexToLightV);                                         \n\
                                                                                        \n\
	vec3 HalfVectorV = normalize(VertexToLightV - normalize(PosV));                     \n\
                                                                                        \n\
	float SpecularFactor = pow(max(0.0, dot(Normal, HalfVectorV)),                      \n\
                              gl_LightSource[Index].spotExponent);                      \n\
	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));                        \n\
                                                                                        \n\
	vec4 ret = gl_LightSource[Index].ambient +                                          \n\
		   gl_LightSource[Index].diffuse * DiffuseFactor +                              \n\
		   gl_LightSource[Index].specular * SpecularFactor;                             \n\
                                        ret.x = 1.0;                                                \n\
	return ret;                                                                         \n\
}                                                                                       \n\
                                                                                        \n\
vec4 GetPointLightIntensity(int Index, vec3 PosV, vec3 Normal)                          \n\
{                                                                                       \n\
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;                    \n\
	float Distance = length(VertexToLightV);                                            \n\
	VertexToLightV = normalize(VertexToLightV);                                         \n\
                                                                                        \n\
	vec3 HalfVectorV = normalize(gl_LightSource[Index].halfVector.xyz);                 \n\
                                                                                        \n\
	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));                        \n\
	float SpecularFactor = 0.0;                                                         \n\
                                                                                        \n\
	if (DiffuseFactor > 0.0) {                                                          \n\
		SpecularFactor = pow(max(0.0, dot(Normal, HalfVectorV)),                        \n\
                            gl_LightSource[Index].spotExponent);                        \n\
	}                                                                                   \n\
                                                                                        \n\
	float Attenuation = 1.0 / (gl_LightSource[Index].constantAttenuation +              \n\
			                   gl_LightSource[Index].linearAttenuation * Distance +     \n\
				               gl_LightSource[Index].quadraticAttenuation * Distance * Distance);   \n\
                                                                                        \n\
	vec4 ret = gl_LightSource[Index].ambient +                                          \n\
	           gl_LightSource[Index].diffuse * DiffuseFactor * Attenuation +            \n\
		   gl_LightSource[Index].specular * SpecularFactor * Attenuation;               \n\
                                                                                        \n\
	return ret;                                                                         \n\
}                                                                                       \n\
                                                                                        \n\
vec4 GetSpotLightIntensity(int Index, vec3 PosV, vec3 Normal)                           \n\
{                                                                                       \n\
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;                    \n\
	float Distance = length(VertexToLightV);                                            \n\
	VertexToLightV = normalize(VertexToLightV);                                         \n\
                                                                                        \n\
	vec3 HalfVectorV = normalize(gl_LightSource[Index].halfVector.xyz);                 \n\
                                                                                        \n\
	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));                        \n\
	float SpecularFactor = 0.0;                                                         \n\
                                                                                        \n\
	if (DiffuseFactor > 0.0)                                                            \n\
		SpecularFactor = pow(max(0.0, dot(Normal, HalfVectorV)),                        \n\
                            gl_LightSource[Index].spotExponent);                        \n\
                                                                                        \n\
	float SpotFactor = dot(-VertexToLightV, normalize(gl_LightSource[Index].spotDirection));       \n\
	float SpotAttenuation = 0.0;                                                        \n\
                                                                                        \n\
	if (SpotFactor > gl_LightSource[Index].spotCosCutoff)                               \n\
		SpotAttenuation = SpotFactor;//pow(SpotFactor, gl_LightSource[Index].spotExponent);          \n\
                                                                                        \n\
	float Attenuation = 1.0 / (gl_LightSource[Index].constantAttenuation +              \n\
			           gl_LightSource[Index].linearAttenuation * Distance +             \n\
				   gl_LightSource[Index].quadraticAttenuation * Distance * Distance);   \n\
	Attenuation *= SpotAttenuation;                                                     \n\
                                                                                        \n\
	vec4 ret = gl_LightSource[Index].ambient +                                          \n\
		   gl_LightSource[Index].diffuse * DiffuseFactor * Attenuation +                \n\
		   gl_LightSource[Index].specular * SpecularFactor * Attenuation;               \n\
                                                                                        \n\
	return ret;                                                                         \n\
}                                                                                       \n\
                                                                                        \n\
vec4 GetLightIntensity(int Index, vec3 PosV, vec3 Normal)                               \n\
{                                                                                       \n\
	if (gl_LightSource[Index].position.w == 0.0)  {                                     \n\
		return GetDirectionalLightIntensity(Index, PosV, Normal);                       \n\
    }                                                                                   \n\
	else if (gl_LightSource[Index].spotCutoff == 180.0) {                               \n\
		return GetPointLightIntensity(Index, PosV, Normal);                             \n\
    }                                                                                   \n\
	else {                                                                              \n\
		return GetSpotLightIntensity(Index, PosV, Normal);                              \n\
    }                                                                                   \n\
}";

BumpMapTechGL::BumpMapTechGL()
{
    if (!AddShaderText(pFS, GL_FRAGMENT_SHADER)) {
        throw new exception;
    }

    if (!AddShaderText(pLightingLib, GL_FRAGMENT_SHADER)) {
        throw new exception;
    }

    if (!AddShaderText(pVS, GL_VERTEX_SHADER)) {
        throw new exception;
    }

    if (!Finalize()) {
        throw new exception;
    }

    m_colorMapLoc = GetUniformLocation("ColorMap");
    printf("Color map location %d\n", m_colorMapLoc);

//    m_texture = GetUniformLocation("TextureSampler");
    glUniform1i(m_colorMapLoc, 0);


    m_bumpMapLoc = GetUniformLocation("BumpMap");
    printf("Bump map location: %d\n", m_bumpMapLoc);

    m_numLightsLoc = GetUniformLocation("gNumLights");
    printf("NumLights location %d\n", m_numLightsLoc);

    m_tangentLoc = GetAttributeLocation("Tangent");
    printf("Tangent location %d\n", m_tangentLoc);
    assert(m_tangentLoc != (GLuint)-1);
}


void BumpMapTechGL::SetNumLights(float NumLights)
{
	glUniform1i(m_numLightsLoc, NumLights);
}


void BumpMapTechGL::SetColorMap(Texture2DGL* pColorMap)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pColorMap->GetTextureHandle());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glUniform1i(m_colorMapLoc, 0);
}

void BumpMapTechGL::SetBumpMap(Texture2DGL* pBumpMap)
{
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pBumpMap->GetTextureHandle());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glUniform1i(m_bumpMapLoc, 1);

}

void BumpMapTechGL::RenderMeshInternal(BaseMeshGL* pMesh)
{
    SetBumpMap((Texture2DGL*)pMesh->GetBumpMap());
    SetColorMap((Texture2DGL*)pMesh->GetColorMap());
    pMesh->SetTangentLoc(m_tangentLoc);
}