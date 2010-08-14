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

#ifndef _ORIENTATION_H
#define	_ORIENTATION_H

#include "interfaces/colossus_math.h"

class Orientation
{
public:
    Orientation();

    void SetPos(float x, float y, float z);

    void SetPos(const Vector3f& Pos)
    {
        m_pos = Pos;
    }

    void SetDirection(float x, float y, float z);

    void SetVelocity(float Velocity);

    void SetAcceleration(float Acceleration);

    void Move(float x, float y, float z);

    void TurnX(float Angle);

    void TurnY(float Angle);

    void TurnZ(float Angle);

    void Update(float TimeDeltaInMillis);

    const Vector3f& GetPos() const;

private:
    Vector3f m_pos;
    Vector3f m_dir;
    float m_velocity;
    float m_acceleration;
};


#endif	/* _ORIENTATION_H */

