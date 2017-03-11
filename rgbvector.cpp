#include "rgbvector.hpp"

RGBAVector::RGBAVector()
    : RGBAVector(Vector3(0, 0, 0))
{
}

RGBAVector::RGBAVector(Vector3 v)
{
    this->r = (unsigned char) v.x;
    this->g = (unsigned char) v.y;
    this->b = (unsigned char) v.z;
    this->a = 255;
}
