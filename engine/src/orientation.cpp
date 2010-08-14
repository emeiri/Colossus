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


#include "interfaces/orientation.h"

Orientation::Orientation()
{
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;

    m_dir.x = 0.0f;
    m_dir.y = 0.0f;
    m_dir.z = 0.0f;

    m_velocity = 0.0f;
    m_acceleration = 0.0f;
}

void Orientation::SetPos(float x, float y, float z)
{
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
}

void Orientation::SetDirection(float x, float y, float z)
{
    m_dir.x = x;
    m_dir.y = y;
    m_dir.z = z;
    m_dir.Normalize();
}

void Orientation::Move(float x, float y, float z)
{
    m_pos.x += x;
    m_pos.y += y;
    m_pos.z += z;
}


void Orientation::TurnX(float Angle)
{

}


void Orientation::TurnY(float Angle)
{

}


void Orientation::TurnZ(float Angle)
{

}

void Orientation::Update(float TimeDeltaInMillis)
{
    const float TimeInSec = TimeDeltaInMillis / 1000;

    // pos(t) = pos(0) + v * t + 1/2 * a * t ^ 2;
    m_velocity += m_acceleration * TimeInSec;
    m_pos += m_dir * (m_velocity * TimeInSec + 0.5f * m_acceleration * TimeInSec * TimeInSec );
}


const Vector3f& Orientation::GetPos() const
{
    return m_pos;
}


void Orientation::SetVelocity(float Velocity)
{
    m_velocity = Velocity;
}


void Orientation::SetAcceleration(float Acceleration)
{
    m_acceleration = Acceleration;
}
