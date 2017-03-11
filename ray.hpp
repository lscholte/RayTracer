#ifndef RAY_HPP
#define RAY_HPP

#include "vector3.hpp"

class Ray
{
    public:
        Ray();
        Ray(const Vector3 origin, const Vector3 direction);

        Vector3 getOrigin() const;
        Vector3 getDirection() const;
        Vector3 getPointAtParameter(float t) const;

    private:
        Vector3 origin, direction;
};

#endif // RAY_HPP
