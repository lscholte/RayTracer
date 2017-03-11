#ifndef SURFACEINSTANCE_HPP
#define SURFACEINSTANCE_HPP

#include "surface.hpp"

class XRotatedSurface : public Surface
{
    public:
        XRotatedSurface(Surface *surface, float degrees);

        virtual bool hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const;

    private:
        Surface *surface;
        float theta;

};

class YRotatedSurface : public Surface
{
    public:
        YRotatedSurface(Surface *surface, float degrees);

        virtual bool hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const;

    private:
        Surface *surface;
        float theta;

};

class ZRotatedSurface : public Surface
{
    public:
        ZRotatedSurface(Surface *surface, float degrees);

        virtual bool hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const;

    private:
        Surface *surface;
        float theta;

};

class TranslatedSurface : public Surface
{
    public:
        TranslatedSurface(Surface *surface, Vector3 offset);

        virtual bool hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const;

    private:
        Surface *surface;
        Vector3 offset;

};

#endif // SURFACEINSTANCE_HPP
