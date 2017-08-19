#include "ray.hpp"

Ray::Ray()
{
}

Ray::Ray(const Vector3 &origin, const Vector3 &direction)
{
    this->origin = origin;
    this->direction = direction;
}

Vector3 Ray::getOrigin() const
{
    return origin;
}

Vector3 Ray::getDirection() const
{
    return direction;
}

Vector3 Ray::getPointAtParameter(float t) const
{
    return origin + direction*t;
}
