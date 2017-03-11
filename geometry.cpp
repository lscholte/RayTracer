#include "geometry.hpp"
#include <random>

Vector3 getRandomPointOnUnitDisc()
{
    float r = rand() / ((float) RAND_MAX);
    float theta = 2*M_PI*(rand() / ((float) RAND_MAX+1));
    return Vector3(sqrt(r)*cos(theta), sqrt(r)*sin(theta), 0);
}

Vector3 getRandomPointOnUnitSphere()
{
    Vector3 p;
    do
    {
        p = Vector3(
                    2 * (rand() / ((float) RAND_MAX+1)) - 1,
                    2 * (rand() / ((float) RAND_MAX+1)) - 1,
                    2 * (rand() / ((float) RAND_MAX+1)) - 1
                );

    } while (p.isZeroVector());
    return p.getUnitVector();
}
