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

#ifndef _PHYSICS_SUBSYSTEM_H
#define	_PHYSICS_SUBSYSTEM_H

#include "base_mesh.h"

class PhysicsSubsystem
{
public:
    PhysicsSubsystem(MeshList& meshList);

    void RenderFrame();

private:
    unsigned int m_frameCount;
    long long m_lastFrameTimeInUsec;
    MeshList& m_meshList;
};

#endif	/* _PHYSICS_SUBSYSTEM_H */

