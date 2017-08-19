#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "ray.hpp"
#include "float.h"

class Material;

struct HitRecord
{
    public:
        float t;
        Vector3 hitLocation;
        Vector3 normal;
        Material *material;
};

class Surface
{
    public:
        virtual bool hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const = 0;

        Surface * rotateAroundX(float degrees);
        Surface * rotateAroundY(float degrees);
        Surface * rotateAroundZ(float degrees);
        Surface * translate(Vector3 offset);
};

class Plane : public Surface
{
    public:
        Plane(Vector3 point, Vector3 normal, Material *material);

        virtual bool hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const;

    private:
        Vector3 point;
        Vector3 normal;
        Material *material;
};

class Sphere : public Surface
{
    public:
        Sphere();
        Sphere(Vector3 centre, float radius, Material *material);

        virtual bool hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const;
        Vector3 getCentre() const;
        float getRadius() const;

    private:
        Vector3 centre;
        float radius;
        Material *material;
};

class Rectangle : public Surface
{
    public:
        Rectangle();
        Rectangle(Vector3 centre, Vector3 normal, float length, float width, Material *material);

        virtual bool hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const;

    private:
        Material *material;
        Vector3 centre, normal;
        float length, width;
        Vector3 a, b, c, d;
};

class Triangle : public Surface
{
    public:
        Triangle();
        Triangle(Vector3 a, Vector3 b, Vector3 c, Material *material);
        
        virtual bool hitWithRay(const Ray r, const float minT, const float maxT, HitRecord &rec) const;
        
    private:
        Material *material;
        Vector3 a, b, c;
        
};

#endif // SURFACE_HPP
