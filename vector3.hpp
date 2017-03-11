#ifndef VECTOR3_HPP
#define VECTOR3_HPP

class Vector3
{
    public:
        float x, y, z;

        Vector3();
        Vector3(float x, float y, float z);

        float getLength() const;
        Vector3 getUnitVector() const;
        float dot(const Vector3 v) const;
        Vector3 cross(const Vector3 v) const;
        bool isZeroVector() const;
};

Vector3 operator+(const Vector3 u, const Vector3 v);
Vector3 operator-(const Vector3 u, const Vector3 v);
Vector3 operator-(const Vector3 v);
Vector3 operator*(const Vector3 u, const Vector3 v);
Vector3 operator*(const Vector3 v, const float s);
Vector3 operator*(const float s, const Vector3 v);
Vector3 operator/(const Vector3 v, const float s);
Vector3 operator+=(Vector3 &u, const Vector3 v);
Vector3 operator-=(Vector3 &u, const Vector3 v);
Vector3 operator*=(Vector3 &u, const float s);
Vector3 operator/=(Vector3 &u, const float s);

#endif // VECTOR3_HPP
