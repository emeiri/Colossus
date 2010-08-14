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


#include <stdio.h>
#include <exception>
#include <stdlib.h>

using namespace std;

#include "GLee.h"
#include "shader.h"
#include "file.h"

Shader::Shader(const char* pVSFile, const char* pFSFile)
{	
	// read the shaders
	long long VSSize = 0;
	long long FSSize = 0;
	char* pFS = NULL;
	char* pVS = ReadFile(pVSFile, &VSSize);
	GLint NumActiveUniforms = 0;

	if (!pVS) {
		goto exit1;
	}

	pFS = ReadFile(pFSFile, &FSSize);

	if (!pFS) {
		goto exit2;
	}

	// create the shader objects
	m_vsObj = glCreateShader(GL_VERTEX_SHADER);

	if (!m_vsObj) {
		goto exit3;
	}

	m_fsObj = glCreateShader(GL_FRAGMENT_SHADER);

	if (!m_fsObj) {
		goto exit4;
	}

	// compile the shaders
	const GLchar* p[1];
	p[0] = pVS;
	GLint Lens[1];
	Lens[0]= (GLint)VSSize;
	glShaderSource(m_vsObj, 1, p, Lens);
	glCompileShader(m_vsObj);
	GLint success;
	glGetShaderiv(m_vsObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];		
		glGetShaderInfoLog(m_vsObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling VS: %s\n", InfoLog);
		goto exit5;
	}

	p[0] = pFS;
	Lens[0]= (GLint)FSSize;
	glShaderSource(m_fsObj, 1, p, Lens);
	glCompileShader(m_fsObj);

	glGetShaderiv(m_fsObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];		
		glGetShaderInfoLog(m_fsObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling FS: %s\n", InfoLog);
		goto exit5;
	}

	m_shaderProg = glCreateProgram();
	if (!m_shaderProg) {
		fprintf(stderr, "Error creating shader program\n");
		goto exit5;
	}

	printf("Created program %d\n", m_shaderProg);

	glAttachShader(m_shaderProg, m_vsObj);	
	glAttachShader(m_shaderProg, m_fsObj);	

	glLinkProgram(m_shaderProg);
	glGetShaderiv(m_shaderProg, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];		
		glGetShaderInfoLog(m_shaderProg, 1024, NULL, InfoLog);
		fprintf(stderr, "Error linking shader program: %s\n", InfoLog);
		goto exit6;
	}

	glValidateProgram(m_shaderProg);
	glGetShaderiv(m_shaderProg, GL_VALIDATE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];		
		glGetShaderInfoLog(m_shaderProg, 1024, NULL, InfoLog);
		fprintf(stderr, "Invalid shader program: %s\n", InfoLog);
		goto exit6;
	}

	glGetShaderiv(m_fsObj, GL_ACTIVE_UNIFORMS ,&NumActiveUniforms);
	printf("Number of active uniforms: %d\n", NumActiveUniforms);

	free(pVS);
	free(pFS);
	return;

exit6:
	glDeleteProgram(m_shaderProg);
exit5:
	glDeleteShader(m_fsObj);
exit4:
	glDeleteShader(m_vsObj);
exit3:
	free(pFS);
exit2:
	free(pVS);
exit1:
return;
	//throw new exception;
}

Shader::~Shader()
{
	glDeleteShader(m_vsObj);
	glDeleteShader(m_fsObj);
	glDeleteProgram(m_shaderProg);
}

void Shader::Enable()
{
	glUseProgram(m_shaderProg);
}


GLuint Shader::GetUniformLocation(const char* pName)
{	
	return glGetUniformLocation(m_shaderProg, pName);
}

