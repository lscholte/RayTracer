#include "surface.hpp"
#include <math.h>
#include <iostream>
#include <float.h>
#include "surfaceinstance.hpp"

Surface * Surface::rotateAroundX(float degrees)
{
    return new XRotatedSurface(this, degrees);
}

Surface * Surface::rotateAroundY(float degrees)
{
    return new YRotatedSurface(this, degrees);
}

Surface * Surface::rotateAroundZ(float degrees)
{
    return new ZRotatedSurface(this, degrees);
}

Surface * Surface::translate(Vector3 offset)
{
    return new TranslatedSurface(this, offset);
}

Plane::Plane(Vector3 point, Vector3 normal, Material *material)
{
    this->point = point;
    this->normal = normal;
    this->material = material;
}

bool Plane::hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const
{
    //Ray is parallel with plane, so it will never intersect it
    if (r.getDirection().dot(normal) == 0)
    {
        return false;
    }

    float temp = ((point-r.getOrigin()).dot(normal)) /
            (r.getDirection().dot(normal));


    if (temp > minT && temp < maxT)
    {
        rec.t = temp;
        rec.hitLocation = r.getPointAtParameter(temp);
        rec.normal = normal;
        rec.material = material;
        return true;
    }


    return false;
}

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(Vector3 centre, Vector3 normal, float length, float width, Material *material)
{
    this->centre = centre;
    this->normal = normal;
    this->width = width;
    this->length = length;
    this->material = material;

    Vector3 u, v, w;
    Vector3 universalUp = Vector3(0, 1, 0);

    //Constructs an orthognal basis to position/orient the camera.
    //w corresponds to moving forward/backward with respect to lookDirection
    //u corresponds to moving left/right with respect to lookDirection
    //v corresponds to moving up/down with respect to lookDirection
    w = (normal);
    u = universalUp.cross(w);

    //This will happen if universalUp is in the same direction as lookAt
    //so pick a new universal up and recalculate u
    if (u.isZeroVector())
    {
        universalUp = Vector3(1, 0, 0);
        u = universalUp.cross(w);
    }

    v = w.cross(u);

    //Make the orthogonal basis an orthonormal basis
    w = w.getUnitVector();
    u = u.getUnitVector();
    v = v.getUnitVector();

    //width axis is u
    //length axis is v

    a = centre - u*width - v*length;
    b = centre + u*width - v*length;
    c = centre + u*width + v*length;
    d = centre - u*width + v*length;
}

bool Rectangle::hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const
{

    //Ray is parallel with Rectangle plane, so it will never intersect it
    if (r.getDirection().dot(normal) == 0)
    {
        return false;
    }

    //Otherwise Ray intersects plane of the rectangle

    float temp = ((centre-r.getOrigin()).dot(normal)) /
            (r.getDirection().dot(normal));

    if (temp > minT && temp < maxT)
    {

        //Math for determining if point is inside rectangle is from
        //http://math.stackexchange.com/questions/190111/how-to-check-if-a-point-is-inside-a-rectangle/190373#190373

        //Point where ray intersects the plane
        Vector3 p = r.getPointAtParameter(temp);

        //Test if point is inside rectangle
        float abDotAp = (b-a).dot(p-a);
        float adDotDp = (d-a).dot(p-a);
        float abDotAb = (b-a).dot(b-a);
        float adDotAd = (d-a).dot(d-a);
        if (abDotAp <= 0 || abDotAp >= abDotAb ||
                adDotDp <= 0 || adDotDp >= adDotAd)
        {
            return false;
        }

        rec.t = temp;
        rec.hitLocation = p;
        rec.normal = normal;
        rec.material = material;
        return true;
    }

    return false;
}

Sphere::Sphere()
{
}

Sphere::Sphere(Vector3 centre, float radius, Material *material)
{
    this->centre = centre;
    this->radius = radius;
    this->material = material;
}

Vector3 Sphere::getCentre() const
{
    return centre;
}

float Sphere::getRadius() const
{
    return radius;
}

bool Sphere::hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const
{

    Vector3 oc = r.getOrigin() - centre;
    float a = r.getDirection().dot(r.getDirection());
    float b = r.getDirection().dot(oc);
    float c = oc.dot(oc) - radius*radius;

    //If equation has 0 or 1 real solutions
    //(ie ray doesn't hit sphere or hits at a tangent)
    if (b*b <= a*c)
    {
        return false;
    }

    float temp = (-b-sqrt(b*b-a*c))/a;
    if (temp > minT && temp < maxT)
    {
        rec.t = temp;
        rec.hitLocation = r.getPointAtParameter(temp);
        rec.normal = (rec.hitLocation - centre) / radius;
        rec.material = material;
        return true;
    }

    temp = (-b+sqrt(b*b-a*c))/a;
    if (temp > minT && temp < maxT)
    {
        rec.t = temp;
        rec.hitLocation = r.getPointAtParameter(temp);
        rec.normal = (rec.hitLocation - centre) / radius;
        rec.material = material;
        return true;
    }

    return false;
}

