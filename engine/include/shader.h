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


#ifndef _SHADER_H_
#define _SHADER_H_

class Shader
{
public:
	Shader(const char* pVSFile, const char* pFSFile);
	~Shader();

	void Enable();

protected:

	GLuint GetUniformLocation(const char* pName);

private:
	GLuint m_shaderProg;
	GLuint m_vsObj;
	GLuint m_fsObj;
};

#endif
