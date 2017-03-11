#include "vector3.hpp"
#include <math.h>

//Variables
float x, y, z;

//Constructors
Vector3::Vector3()
    : Vector3(0, 0, 0)
{
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

//Methods
float Vector3::getLength() const
{
    return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::getUnitVector() const
{
    if (this->isZeroVector())
    {
        //TODO: throw exception
    }
    return *this / this->getLength();
}

float Vector3::dot(const Vector3 v) const
{
    return x*v.x + y*v.y + z*v.z;
}

Vector3 Vector3::cross(const Vector3 v) const
{
    Vector3 w;
    w.x = y*v.z - z*v.y;
    w.y = z*v.x - x*v.z;
    w.z = x*v.y - y*v.x;
    return w;
}

bool Vector3::isZeroVector() const
{
    return x == 0 && y == 0 && z == 0;
}

Vector3 operator+(const Vector3 u, const Vector3 v)
{
    return Vector3(u.x+v.x, u.y+v.y, u.z+v.z);
}

Vector3 operator-(const Vector3 u, const Vector3 v)
{
    return Vector3(u.x-v.x, u.y-v.y, u.z-v.z);
}

Vector3 operator-(const Vector3 v)
{
    return -1*v;
}

Vector3 operator*(const Vector3 u, const Vector3 v)
{
    return Vector3(u.x*v.x, u.y*v.y, u.z*v.z);
}

Vector3 operator*(const Vector3 v, const float s)
{
    return Vector3(v.x*s, v.y*s, v.z*s);
}

Vector3 operator*(const float s, const Vector3 v)
{
    return v*s;
}

Vector3 operator/(const Vector3 v, const float s)
{
    return Vector3(v.x/s, v.y/s, v.z/s);
}

Vector3 operator+=(Vector3 &u, const Vector3 v)
{
    u.x += v.x;
    u.y += v.y;
    u.z += v.z;
    return u;
}

Vector3 operator-=(Vector3 &u, const Vector3 v)
{
    u.x -= v.x;
    u.y -= v.y;
    u.z -= v.z;
    return u;
}

Vector3 operator*=(Vector3 &u, const float s)
{
    u.x *= s;
    u.y *= s;
    u.z *= s;
    return u;
}

Vector3 operator/=(Vector3 &u, const float s)
{
    u.x /= s;
    u.y /= s;
    u.z /= s;
    return u;
}
