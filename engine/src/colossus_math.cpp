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

#include "interfaces/colossus_math.h"


Vector3f& Vector3f::Normalize()
{
    float Length = sqrtf(x * x + y * y + z * z);
    x /= Length;
    y /= Length;
    z /= Length;

    return *this;
}

void Vector3f::Rotate(float Angle, const Vector3f& Axis)
{
    /*printf("\n");
    printf("Angle %f\n", Angle);
    printf("Before %f %f %f\n", x, y, z);*/
    
    const float SinHalfAngle = sinf(ToRadian(Angle/2));
    const float CosHalfAngle = cosf(ToRadian(Angle/2));

    //printf("sin %f cos %f\n", SinHalfAngle, CosHalfAngle);
    
    const float Rx = Axis.x * SinHalfAngle;
    const float Ry = Axis.y * SinHalfAngle;
    const float Rz = Axis.z * SinHalfAngle;
    const float Rw = CosHalfAngle;
    //printf("Rotation quaternion %f %f %f %f\n", Rx, Ry, Rz, Rw);
    Quaternion RotationQ(Rx, Ry, Rz, Rw);

    Quaternion ConjugateQ = RotationQ.Conjugate();
    ConjugateQ.Normalize();
    //printf("Conjugate %f %f %f %f\n", ConjugateQ.x, ConjugateQ.y, ConjugateQ.z, ConjugateQ.w);
    Quaternion W = RotationQ * (*this);
  //  printf("Q * View: %f %f %f %f\n", W.x, W.y, W.z, W.w);
        
    W *= ConjugateQ;
//    printf("Q * View * Conjugate: %f %f %f %f\n", W.x, W.y, W.z, W.w);

    x = W.x;
    y = W.y;
    z = W.z;

    //printf("After %f %f %f\n", x, y, z);
}

void Vector3f::Print(bool isEndline) const
{
    printf("(%.02f, %.02f, %.02f)", x, y, z);
    if (isEndline) {
        printf("\n");
    }
}


Vector3f CrossProduct(const Vector3f& l, const Vector3f& r)
{
    float x = l.y * r.z - l.z * r.y;
    float y = l.z * r.x - l.x * r.z;
    float z = l.x * r.y - l.y * r.x;

    return Vector3f(x, y, z);
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

void Quaternion::Normalize()
{
    float Length = sqrtf(x * x + y * y + z * z + w * w);

    x /= Length;
    y /= Length;
    z /= Length;
    w /= Length;
}


Quaternion Quaternion::Conjugate()
{
    Quaternion ret(-x, -y, -z, w);
    return ret;
}

Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
    const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
    const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
    //printf("! %f    %f %f  %f %f  %f %f  %f %f\n", x, l.x, r.w, l.w, r.x, l.y, r.z, l.z, r.y);
    const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
    const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);
//    printf("! %f    %f %f  %f %f  %f %f  %f %f\n", z, l.z, r.w, l.w, r.z, l.x, r.y, l.y, r.x);

    Quaternion ret(x, y, z, w);

    return ret;
}

Quaternion operator*(const Quaternion& q, const Vector3f& v)
{
    const float w = - (q.x * v.x) - (q.y * v.y) - (q.z * v.z);
    const float x =   (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
//    printf("%f    %f %f %f %f %f %f\n", x, q.w, v.x, q.y, v.z, q.z, v.y);
    const float y =   (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
    const float z =   (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

    Quaternion ret(x, y, z, w);

    return ret;
}

Quaternion& Quaternion::operator*=(Quaternion& r)
{
    *this = operator*(*this, r);

    return * this;   
}

