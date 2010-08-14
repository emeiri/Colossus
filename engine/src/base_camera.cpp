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
#include <math.h>
#include <GL/glut.h>

#include "base_camera.h"

const static float StepSize = 1.0f;

void CameraBase::Init()
{
    Vector3f Dir = m_Target - m_Pos;
    Dir.Normalize();
    //Dir.Print();
    m_AngleH = -ToDegree(asin(Dir.z));
    //printf("AngleH %f\n", m_AngleH);
    m_AngleV = ToDegree(asin(Dir.y));
    m_isInitialMousePosKnown = false;
    m_OnUpperEdge = false;
    m_OnLowerEdge = false;
    m_OnLeftEdge  = false;
    m_OnRightEdge = false;
    m_mousePos.x  = m_mousePos.y = 0;
    m_velocity    = 1.0f;
}

CameraBase::CameraBase(int WindowWidth, int WindowHeight) : ICamera(WindowWidth, WindowHeight)
{
    m_Pos = Vector3f( 0.0f, 0.0f, 0.0f );
    m_windowWidth = WindowWidth;
    m_windowHeight = WindowHeight;

    Init();
}

CameraBase::CameraBase(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
        : ICamera(WindowWidth, WindowHeight)
{
    Move(Pos, Target, Up);
    m_windowWidth  = WindowWidth;
    m_windowHeight = WindowHeight;

    Init();
    Update();
}

void CameraBase::SetVelocity(float Velocity)
{
    m_velocity = Velocity;
}

void CameraBase::Move(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
{
    m_Pos    = Pos;
    m_Target = Target;
    m_Up     = Up;

    //printf("Camera target: "); m_Target.Print();
}


bool CameraBase::OnKeyboard(int Key, int x, int y)
{
    bool Ret = false;

    switch (Key) {

    case GLUT_KEY_UP:
        //printf("Pos: "); m_Pos.Print(true);
     //   printf("Dir: "); m_Dir.Print(true);
   //     printf("Target: "); m_Dir.Print(true);
        {
            Vector3f Dir = m_Target - m_Pos;
            Dir.Normalize();
            Dir *= StepSize;
            m_Pos += Dir;
            m_Target += Dir;
            //printf("New pos: "); m_Pos.Print(true);
            //printf("New target: "); Dir.Print(true);
            Ret = true;
        }

        break;

    case GLUT_KEY_DOWN:
        {
            Vector3f Dir = m_Target - m_Pos;
            Dir.Normalize();
            Dir *= StepSize;
            m_Pos -= Dir;
            Ret = true;
        }

        break;

    case GLUT_KEY_LEFT:
        {
            Vector3f Dir = m_Target - m_Pos;
            Dir.Normalize();
            Vector3f Right = CrossProduct(Dir, m_Up);
            Right *= StepSize;
            m_Pos -= Right;
            m_Target -= Right;
            Ret = true;
        }
        break;

    case GLUT_KEY_RIGHT:
        {
            Vector3f Dir = m_Target - m_Pos;
            Dir.Normalize();
            Vector3f Right = CrossProduct(Dir, m_Up);
            Right *= StepSize;
            m_Pos += Right;
            m_Target += Right;
            Ret = true;
        }
        break;
    }

    return Ret;
}


void CameraBase::OnPassiveMouseMov(int x, int y)
{
    int DeltaX = x - m_mousePos.x;
    int DeltaY = y - m_mousePos.y;

    if (m_isInitialMousePosKnown) {
        m_AngleH -= (float)DeltaX / 20.0f;
        m_AngleV += (float)DeltaY / 20.0f;

        if (DeltaX == 0) {
            if (x == 0) {
                m_AngleH += 1.0f;
                m_OnLeftEdge = true;
            }
            else if (x == (m_windowWidth - 1)) {
                m_AngleH -= 1.0f;
                m_OnRightEdge = true;
            }
        }
        else {
            m_OnLeftEdge = false;
            m_OnRightEdge = false;
        }

        if (DeltaY == 0) {
            if (y == 0) {
                DecAngleV();
                m_OnUpperEdge = true;
            }
            else if (y == (m_windowHeight - 1)) {
                IncAngleV();
                m_OnLowerEdge = true;
            }
        }
        else {
            m_OnUpperEdge = false;
            m_OnLowerEdge = false;
        }

        Update();
    }
    else
    {
        m_isInitialMousePosKnown = true;
    }

    //printf("  AngleH %f\n", m_AngleH);
    m_mousePos.x = x;
    m_mousePos.y = y;
}

void CameraBase::OnRender()
{
    bool ShouldUpdate = false;

    if (m_OnLeftEdge) {
        m_AngleH += 1.0f;
        ShouldUpdate = true;
    }
    else if (m_OnRightEdge) {
        m_AngleH -= 1.0f;
        ShouldUpdate = true;
    }

    if (m_OnUpperEdge) {
        DecAngleV();
        ShouldUpdate = true;
    }
    else if (m_OnLowerEdge) {
        IncAngleV();
        ShouldUpdate = true;
    }

    if (ShouldUpdate) {
        Update();
    }

    Apply();
}


void CameraBase::Update()
{
    const Vector3f Yaxis(0.0f, 1.0f, 0.0f);
    const Vector3f Xaxis(1.0f, 0.0f, 0.0f);
    Vector3f View(1.0f, 0.0f, 0.0f);
    View.Rotate(m_AngleH, Yaxis);
   // printf("%.02f\n", m_AngleH);
    View.Normalize();
    View.Rotate(m_AngleV, Xaxis);
    View.Normalize();
    View *= m_velocity;
    m_Target = m_Pos + View;
    //printf("  Camera target: "); m_Target.Print();
}

void CameraBase::IncAngleV()
{
    if (m_AngleV < 170.0f) {
        m_AngleV += 0.40f;
    }
}

void CameraBase::DecAngleV()
{
    if (m_AngleV > 20.0f) {
        m_AngleV -= 0.40f;
    }
}
