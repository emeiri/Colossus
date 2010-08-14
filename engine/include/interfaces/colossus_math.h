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


#ifndef _GL_MATH_H_
#define _GL_MATH_H_

#define ToRadian(x) (x) * M_PI / 180.0f
#define ToDegree(x) (x) * 180.0f / M_PI



struct Vector2i
{
    int x;
    int y;
};

struct Vector3i
{
    int x;
    int y;
    int z;
};

struct Vector2f
{
    float x;
    float y;

    Vector2f()
    {
    }

    Vector2f(float x1, float y1)
    {
            x = x1;
            y = y1;
    }
};

struct Vector3f
{
    float x;
    float y;
    float z;

    Vector3f() {}

    Vector3f(float x1, float y1, float z1)
    {
            x = x1;
            y = y1;
            z = z1;
    }

    Vector3f& Normalize();

    Vector3f& operator+=(const Vector3f& r)
    {
            x += r.x;
            y += r.y;
            z += r.z;

            return *this;
    }

    Vector3f& operator-=(Vector3f& r)
    {
            x -= r.x;
            y -= r.y;
            z -= r.z;

            return *this;
    }

    Vector3f& operator*=(float f)
    {
            x *= f;
            y *= f;
            z *= f;

            return *this;
    }

    operator float*()
    {
        return &x;
    }

    void Rotate(float Angle, const Vector3f& Axis);

    void Print(bool isEndline = true) const;
};

inline Vector3f operator+(Vector3f& l, Vector3f& r)
{
	Vector3f Ret(l.x + r.x, 
                     l.y + r.y,
                     l.z + r.z);

	return Ret;
}

inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x - r.x, 
                     l.y - r.y,
		     l.z - r.z);

	return Ret;
}

inline Vector3f operator*(Vector3f& v, float f)
{
    Vector3f Ret(v.x * f, v.y * f, v.z * f);

    return Ret;
}


Vector3f CrossProduct(const Vector3f& l, const Vector3f& r);

struct Vector4f
{
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        float v[4];
    };

    Vector4f() {}

    Vector4f(float x1, float y1, float z1, float w1)
    {
        x = x1;
        y = y1;
        z = z1;
        w = w1;
    }

    operator float*()
    {
        return &v[0];
    }
};


struct Matrix4f
{
    float m[4][4];
};

struct Quaternion
{
    float x, y, z, w;

    Quaternion(float _x, float _y, float _z, float _w);

    void Normalize();

    Quaternion Conjugate();

    Quaternion& operator*=(Quaternion& r);
 };

Quaternion operator*(const Quaternion& l, const Quaternion& r);

Quaternion operator*(const Quaternion& q, const Vector3f& v);

#endif
