#ifndef RGBVECTOR_HPP
#define RGBVECTOR_HPP

#include "vector3.hpp"

class RGBAVector
{
    public:
        unsigned char r, g, b, a;

        RGBAVector();
        RGBAVector(Vector3 v);
};

#endif // RGBVECTOR_HPP
