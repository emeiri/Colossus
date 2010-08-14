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


#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <exception>
#include <string.h>

#include "backend/GL/base_technique_gl.h"
#include "file.h"
#include "base_3d_app.h"

BaseTechniqueGL::BaseTechniqueGL()
{
    m_shaderProg = glCreateProgram();
    if (!m_shaderProg) {
        fprintf(stderr, "Error creating shader program\n");
        throw new exception;
    }

    printf("Created shader program\n");
}


BaseTechniqueGL::~BaseTechniqueGL()
{
	for (ObjectList::const_iterator it = m_objects.begin() ; it != m_objects.end() ; it++) {
		glDeleteShader(*it);
	}

	glDeleteProgram(m_shaderProg);
}

bool BaseTechniqueGL::AddShaderInternal(const char* pShaderText, unsigned int ShaderSize, GLenum ShaderType)
{
    GLint NumActiveUniforms = 0;
    GLuint ShaderObj = 0;

    // create the shader objects
    ShaderObj = glCreateShader(ShaderType);

    if (!ShaderObj) {
        assert(0);
        goto exit1;
    }

    // compile the shader
    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lens[1];
    Lens[0]= (GLint)ShaderSize;
    glShaderSource(ShaderObj, 1, p, Lens);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
            GLchar InfoLog[1024];
            glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
            fprintf(stderr, "Error compiling shader %d: %s\n", ShaderType, InfoLog);
            assert(0);
            goto exit2;
    }

    glAttachShader(m_shaderProg, ShaderObj);

    glLinkProgram(m_shaderProg);
    glGetShaderiv(m_shaderProg, GL_LINK_STATUS, &success);

    if (!success) {
            GLchar InfoLog[1024] = "";
            glGetShaderInfoLog(m_shaderProg, 1024, NULL, InfoLog);
            assert(0);
            fprintf(stderr, "Error linking shader program: %s\n", InfoLog);
    }

    glGetShaderiv(m_shaderProg, GL_ACTIVE_UNIFORMS ,&NumActiveUniforms);
    printf("Compiled shader %d, number of active uniforms: %d\n", ShaderType, NumActiveUniforms);

    m_objects.push_back(ShaderObj);

    return true;

exit2:
    glDeleteShader(ShaderObj);
exit1:
    return false;
}

bool BaseTechniqueGL::AddShaderFile(const char* pFilename, GLenum ShaderType)
{
    assert( (ShaderType == GL_VERTEX_SHADER) || (ShaderType == GL_FRAGMENT_SHADER) );

    // read the shader file
    long long ShaderSize = 0;
    char* pShaderText = ReadFile(pFilename, &ShaderSize);

    bool Ret = false;

    if (pShaderText) {
        Ret = AddShaderInternal(pShaderText, (unsigned int)ShaderSize, ShaderType);
        free(pShaderText);
    }

    return Ret;
}


bool BaseTechniqueGL::Finalize()
{
	GLint success = 0;

	return true;
	glLinkProgram(m_shaderProg);
	glGetShaderiv(m_shaderProg, GL_LINK_STATUS, &success);

	if (!success) {
		GLchar InfoLog[1024] = "";		
		glGetShaderInfoLog(m_shaderProg, 1024, NULL, InfoLog);
		fprintf(stderr, "Error linking shader program: %s\n", InfoLog);		
	}
	else {
		glValidateProgram(m_shaderProg);
		glGetShaderiv(m_shaderProg, GL_VALIDATE_STATUS, &success);
		if (!success) {
			GLchar InfoLog[1024];		
			glGetShaderInfoLog(m_shaderProg, 1024, NULL, InfoLog);
			fprintf(stderr, "Invalid shader program: %s\n", InfoLog);
		}
	}
	
	return (success != 0);
}

void BaseTechniqueGL::Enable()
{
	glUseProgram(m_shaderProg);
}

void BaseTechniqueGL::Disable()
{
	glUseProgram(0);
}

GLuint BaseTechniqueGL::GetUniformLocation(const char* pName)
{	
	return glGetUniformLocation(m_shaderProg, pName);
}

GLint BaseTechniqueGL::GetAttributeLocation(const char* pName) const
{
    return glGetAttribLocation(m_shaderProg, pName);
}


bool BaseTechniqueGL::AddShaderText(const char* pShaderText, GLenum ShaderType)
{
    return AddShaderInternal(pShaderText, strlen(pShaderText), ShaderType);
}

void BaseTechniqueGL::RenderMesh(BaseMeshGL* pMesh)
{
    RenderMeshInternal(pMesh);
    const Vector3f& Pos = pMesh->GetOrientation().GetPos();
    glPushMatrix();    
    glTranslatef(Pos.x, Pos.y, Pos.z);
    glScalef(pMesh->GetScale(), pMesh->GetScale(), pMesh->GetScale());
    pMesh->Render();
    glPopMatrix();
}

