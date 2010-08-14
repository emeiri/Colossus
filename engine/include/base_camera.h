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


#ifndef _CameraBase_H_
#define _CameraBase_H_

#include "interfaces/camera.h"

class CameraBase : public ICamera
{
public:
    CameraBase(int WindowWidth, int WindowHeight);

    CameraBase(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

    void SetVelocity(float Velocity);

    void Move(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

    bool OnKeyboard(int Key, int x, int y);

    void OnPassiveMouseMov(int x, int y);

    void OnRender();

    virtual void Apply() = 0;

    const Vector3f& GetPos() const
    {
        return m_Pos;
    }

protected:
    Vector3f m_Pos;
    Vector3f m_Target;
    Vector3f m_Up;

private:
    void Init();
    void Update();
    void IncAngleV();
    void DecAngleV();

    int m_windowWidth;
    int m_windowHeight;

    float m_velocity;

    float m_AngleH;
    float m_AngleV;

    bool m_isInitialMousePosKnown;
    bool m_OnUpperEdge;
    bool m_OnLowerEdge;
    bool m_OnLeftEdge;
    bool m_OnRightEdge;

    Vector2i m_mousePos;
};


#endif
