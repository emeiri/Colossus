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


#ifndef _BASE_TECHNIQUE_H_
#define _BASE_TECHNIQUE_H_

#include <list>

#include "GLee.h"
#include "interfaces/orientation.h"
#include "base_mesh_gl.h"

using namespace std;

class BaseTechniqueGL
{
public:
    BaseTechniqueGL();

    ~BaseTechniqueGL();

    bool AddShaderFile(const char* pFilename, GLenum ShaderType);

    bool AddShaderText(const char* pShaderText, GLenum ShaderType);

    bool Finalize();

    void Enable();
    void Disable();

    void RenderMesh(BaseMeshGL* pMesh);

protected:
    GLuint GetUniformLocation(const char* pName);
    GLint GetAttributeLocation(const char* pName) const;

    bool AddShaderInternal(const char* pShaderText, unsigned int Length, GLenum ShaderType);

    virtual void RenderMeshInternal(BaseMeshGL* pMesh) {};

private:
    typedef list<GLuint> ObjectList;
    ObjectList m_objects;
    GLuint m_shaderProg;
};

#endif
