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


#include <sys/time.h>

#include "physics_subsystem.h"


PhysicsSubsystem::PhysicsSubsystem(MeshList& meshList) : m_meshList(meshList)
{
    m_lastFrameTimeInUsec = 0;
    m_frameCount = 0;
}

void PhysicsSubsystem::RenderFrame()
{
    long long TimeDelta = 0;

    struct timeval Now;
    gettimeofday(&Now, NULL);
    const long long NowInUsec = (long long)Now.tv_sec * 1000000 + Now.tv_usec;

    if (m_frameCount > 0) {
        TimeDelta = NowInUsec - m_lastFrameTimeInUsec;
    }

    m_lastFrameTimeInUsec = NowInUsec;

    for (MeshList::iterator it = m_meshList.begin() ; it != m_meshList.end() ; it++) {
        IMesh* pMesh = *it;

        pMesh->GetOrientation().Update(TimeDelta / 1000);
    }


    m_frameCount++;
}