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


#include "backend/GL/texture_tech_gl.h"

static const char* pVS = "                              \n\
// vectors required by the fragment shader              \n\
varying vec3 NormalV;                                   \n\
varying vec3 PosV;                                      \n\
                                                        \n\
                                                        \n\
void main()                                             \n\
{                                                       \n\
	gl_Position = ftransform();                         \n\
                                                        \n\
	gl_TexCoord[0] = gl_MultiTexCoord0;                 \n\
                                                        \n\
	NormalV = (gl_NormalMatrix * gl_Normal).xyz;        \n\
	PosV = (gl_ModelViewMatrix * gl_Vertex).xyz;        \n\
}";


static const char* pFS = "                                                    \n\
uniform int gNumLights;                                                       \n\
                                                                              \n\
varying vec3 NormalV;                                                         \n\
varying vec3 PosV;                                                            \n\
                                                                              \n\
uniform sampler2D TextureSampler;                                             \n\
                                                                              \n\
vec4 GetLightIntensity(int Index, vec3 PosV, vec3 Normal);                    \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    vec4 Texel = texture2D(TextureSampler, gl_TexCoord[0].st);                \n\
    vec3 Normal = normalize(NormalV);                                         \n\
    if (Texel.x <= 0.001) {                                                   \n\
        gl_FragColor = vec4(0.4, 0.4, 0.4, 1.0);                              \n\
    }                                                                         \n\
    else {                                                                    \n\
        gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);                              \n\
                                                                              \n\
        for (int i = 0 ; i < gNumLights ; i++)                                \n\
        {                                                                     \n\
            gl_FragColor += Texel * GetLightIntensity(i, PosV, Normal);       \n\
        }                                                                     \n\
    }                                                                         \n\
}";


static const char* pLightingLib = "                                                                     \n\
vec4 GetDirectionalLightIntensity(int Index, vec3 PosV, vec3 Normal)                                    \n\
{                                                                                                       \n\
	// should be simply the position    \n\
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;\n\
	VertexToLightV = normalize(VertexToLightV);\n\
\n\
	vec3 HalfVectorV = normalize(VertexToLightV - normalize(PosV));\n\
\n\
	float SpecularFactor = pow(max(0.0, dot(Normal, HalfVectorV)), gl_LightSource[Index].spotExponent);\n\
	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));\n\
\n\
	vec4 ret = gl_LightSource[Index].ambient + \n\
		   gl_LightSource[Index].diffuse * DiffuseFactor + \n\
		   gl_LightSource[Index].specular * SpecularFactor;\n\
\n\
	return ret;\n\
}\n\
\n\
vec4 GetPointLightIntensity(int Index, vec3 PosV, vec3 Normal)\n\
{\n\
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;\n\
	float Distance = length(VertexToLightV);\n\
	VertexToLightV = normalize(VertexToLightV);\n\
\n\
	//vec3 HalfVectorV = normalize(VertexToLightV - normalize(PosV));\n\
	vec3 HalfVectorV = normalize(gl_LightSource[Index].halfVector.xyz);\n\
\n\
	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));\n\
	float SpecularFactor = 0.0;\n\
\n\
	if (DiffuseFactor > 0.0) {\n\
		SpecularFactor = max(0.0, dot(Normal, HalfVectorV)); \n\
		SpecularFactor = pow(SpecularFactor, gl_LightSource[Index].spotExponent);\n\
	}\n\
	\n\
	float Attenuation = 1.0 / (gl_LightSource[Index].constantAttenuation + \n\
			           gl_LightSource[Index].linearAttenuation * Distance + \n\
				   gl_LightSource[Index].quadraticAttenuation * Distance * Distance);\n\
\n\
	vec4 ret = gl_LightSource[Index].ambient + \n\
	           gl_LightSource[Index].diffuse * DiffuseFactor * Attenuation + \n\
		   gl_LightSource[Index].specular * SpecularFactor * Attenuation;\n\
\n\
	return ret;\n\
}\n\
\n\
vec4 GetSpotLightIntensity(int Index, vec3 PosV, vec3 Normal)                                           \n\
{                                                                                                       \n\
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;                                    \n\
	float Distance = length(VertexToLightV);                                                            \n\
	VertexToLightV = normalize(VertexToLightV);                                                         \n\
                                                                                                        \n\
	vec3 HalfVectorV = normalize(gl_LightSource[Index].halfVector.xyz);                                 \n\
                                                                                                        \n\
	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));                                        \n\
	float SpecularFactor = 0.0;                                                                         \n\
                                                                                                        \n\
	if (DiffuseFactor > 0.0)                                                                            \n\
		SpecularFactor = pow(max(0.0, dot(Normal, HalfVectorV)), gl_LightSource[Index].spotExponent);   \n\
                                                                                                        \n\
	float Attenuation = 1.0 / (gl_LightSource[Index].constantAttenuation +                              \n\
			           gl_LightSource[Index].linearAttenuation * Distance +                             \n\
				   gl_LightSource[Index].quadraticAttenuation * Distance * Distance);                   \n\
                                                                                                        \n\
	float SpotFactor = dot(-VertexToLightV, normalize(gl_LightSource[Index].spotDirection));            \n\
                                                                                                        \n\
	if (SpotFactor > gl_LightSource[Index].spotCosCutoff)                                               \n\
		Attenuation *= SpotFactor;//pow(SpotFactor, gl_LightSource[Index].spotExponent);                             \n\
    else                                                                                                \n\
        Attenuation = 0.0;                                                                              \n\
                                                                                                        \n\
	vec4 ret = gl_LightSource[Index].ambient +                                                          \n\
		   gl_LightSource[Index].diffuse * DiffuseFactor * Attenuation +                                \n\
		   gl_LightSource[Index].specular * SpecularFactor * Attenuation;                               \n\
	return ret;                                                                                         \n\
}                                                                                                       \n\
                                                                                                        \n\
vec4 GetLightIntensity(int Index, vec3 PosV, vec3 Normal)                                               \n\
{                                                                                                       \n\
	if (gl_LightSource[Index].position.w == 0.0)                                                        \n\
		return GetDirectionalLightIntensity(Index, PosV, Normal);                                       \n\
	else if (gl_LightSource[Index].spotCutoff == 180.0)                                                 \n\
		return GetPointLightIntensity(Index, PosV, Normal);                                             \n\
	else                                                                                                \n\
		return GetSpotLightIntensity(Index, PosV, Normal);                                              \n\
}";

TextureTechGL::TextureTechGL()
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

    m_texture = GetUniformLocation("TextureSampler");
 //   glUniform1i(m_texture, 0);

    m_numLightsLoc = GetUniformLocation("gNumLights");
}


void TextureTechGL::SetNumLights(float NumLights)
{
	glUniform1i(m_numLightsLoc, NumLights);
}


void TextureTechGL::SetColorMap(Texture2DGL* pColorMap)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pColorMap->GetTextureHandle());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glUniform1i(m_texture, 0);
}


void TextureTechGL::RenderMeshInternal(BaseMeshGL* pMesh)
{
    SetColorMap((Texture2DGL*)pMesh->GetColorMap());
}