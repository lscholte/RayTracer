#include "surfaceinstance.hpp"
#include "math.h"

Vector3 rotateAboutX(Vector3 v, float theta)
{
    Vector3 w;
    w.x = v.x;
    w.y = cos(theta)*v.y - sin(theta)*v.z;
    w.z = sin(theta)*v.y + cos(theta)*v.z;
    return w;
}

Vector3 rotateAboutY(Vector3 v, float theta)
{
    Vector3 w;
    w.x = cos(theta)*v.x - sin(theta)*v.z;
    w.y = v.y;
    w.z = sin(theta)*v.x + cos(theta)*v.z;
    return w;
}

Vector3 rotateAboutZ(Vector3 v, float theta)
{
    Vector3 w;
    w.x = cos(theta)*v.x - sin(theta)*v.y;
    w.y = sin(theta)*v.x + cos(theta)*v.y;
    w.z = v.z;
    return w;
}

XRotatedSurface::XRotatedSurface(Surface *surface, float degrees)
{
    this->surface = surface;
    this->theta = degrees * M_PI/180;
}

bool XRotatedSurface::hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const
{
    Vector3 origin = rotateAboutX(r.getOrigin(), theta);
    Vector3 direction = rotateAboutX(r.getDirection(), theta);
    Ray rotatedRay = Ray(origin, direction);

    if (surface->hitWithRay(rotatedRay, minT, maxT, rec)) {
        Vector3 hitLocation = rotateAboutX(rec.hitLocation, -theta);
        Vector3 normal = rotateAboutX(rec.normal, -theta);

        rec.hitLocation = hitLocation;
        rec.normal = normal;
        return true;
    }
    return false;
}

YRotatedSurface::YRotatedSurface(Surface *surface, float degrees)
{
    this->surface = surface;
    this->theta = degrees * M_PI/180;
}

bool YRotatedSurface::hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const
{
    Vector3 origin = rotateAboutY(r.getOrigin(), theta);
    Vector3 direction = rotateAboutY(r.getDirection(), theta);
    Ray rotatedRay = Ray(origin, direction);

    if (surface->hitWithRay(rotatedRay, minT, maxT, rec)) {
        Vector3 hitLocation = rotateAboutY(rec.hitLocation, -theta);
        Vector3 normal = rotateAboutY(rec.normal, -theta);

        rec.hitLocation = hitLocation;
        rec.normal = normal;
        return true;
    }
    return false;
}

ZRotatedSurface::ZRotatedSurface(Surface *surface, float degrees)
{
    this->surface = surface;
    this->theta = degrees * M_PI/180;
}

bool ZRotatedSurface::hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const
{
    Vector3 origin = rotateAboutZ(r.getOrigin(), theta);
    Vector3 direction = rotateAboutZ(r.getDirection(), theta);
    Ray rotatedRay = Ray(origin, direction);

    if (surface->hitWithRay(rotatedRay, minT, maxT, rec)) {
        Vector3 hitLocation = rotateAboutZ(rec.hitLocation, -theta);
        Vector3 normal = rotateAboutZ(rec.normal, -theta);

        rec.hitLocation = hitLocation;
        rec.normal = normal;
        return true;
    }
    return false;
}

TranslatedSurface::TranslatedSurface(Surface *surface, Vector3 offset)
{
    this->surface = surface;
    this->offset = offset;
}

bool TranslatedSurface::hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const
{
    Ray translatedRay = Ray(r.getOrigin()-offset, r.getDirection());

    if (surface->hitWithRay(translatedRay, minT, maxT, rec)) {
        rec.hitLocation += offset;
        return true;
    }
    return false;
}
