#include "material.hpp"
#include "geometry.hpp"
#include <random>

Vector3 Material::emitted()
{
    //By default materials do not emit light
    //unless this method is overridden
    return Vector3(0, 0, 0);
}

Diffuse::Diffuse(const Vector3 &albedo)
{
    this->albedo = albedo;
}

bool Diffuse::scatter(const Ray &incomingRay,
                     const HitRecord &rec,
                     Vector3 &attenuation,
                     Ray &scatteredRay) const
{
    scatteredRay = Ray(rec.hitLocation, rec.normal + getRandomPointOnUnitSphere());
    attenuation = albedo;
    return true;
}


Metal::Metal(const Vector3 &albedo)
    : Metal(albedo, 0.0)
{
}

Metal::Metal(const Vector3 &albedo, float fuzz)
{
    this->albedo = albedo;
    if (fuzz < 1)
    {
        this->fuzz = fuzz;
    }
    else
    {
        this->fuzz = 1;
    }
}

bool Metal::scatter(const Ray &incomingRay,
                     const HitRecord &rec,
                     Vector3 &attenuation,
                     Ray &scatteredRay) const
{
    Vector3 reflected = reflect(incomingRay.getDirection().getUnitVector(), rec.normal);
    scatteredRay = Ray(rec.hitLocation, reflected + getRandomPointOnUnitSphere()*fuzz);
    attenuation = albedo;
    return scatteredRay.getDirection().dot(rec.normal) > 0;
}

Dielectric::Dielectric(float refractiveIndex)
{
    this->refractiveIndex = refractiveIndex;
}

bool Dielectric::scatter(const Ray &incomingRay, const HitRecord &rec, Vector3 &attenuation, Ray &scatteredRay) const
{
    Vector3 normal;
    Vector3 reflected = reflect(incomingRay.getDirection(), rec.normal);
    float refractiveIndexFrom, refractiveIndexTo;
    attenuation = Vector3(1.0, 1.0, 1.0);
    Vector3 refracted;

    float reflectProbability;
    float cosine;

    //If angle between normal and incoming ray is more than 90 degrees.
    //In other words, if ray is exiting this material
    float dotProduct = incomingRay.getDirection().dot(rec.normal);
    if (dotProduct > 0)
    {
        normal = -rec.normal;
        refractiveIndexFrom = refractiveIndex;
        refractiveIndexTo = 1.0;
    }
    //Otherwise ray is entering this material
    else
    {
        normal = rec.normal;
        refractiveIndexFrom = 1.0;
        refractiveIndexTo = refractiveIndex;
    }

    if (refract(incomingRay.getDirection(), normal, refractiveIndexFrom, refractiveIndexTo, refracted, cosine))
    {
        reflectProbability = getSchlickApproximation(cosine, refractiveIndexFrom, refractiveIndexTo);
    }
    else
    {
        reflectProbability = 1.0;
    }

    //The ray has a chance of being reflected instead of refracted
    //based on the probability of reflection produced by
    if (rand() / ((float) RAND_MAX+1) < reflectProbability)
    {
        scatteredRay = Ray(rec.hitLocation, reflected);
    }
    else
    {
        scatteredRay = Ray(rec.hitLocation, refracted);
    }
    return true;
}

Light::Light()
{
}

Light::Light(const Vector3 &colour)
{
    this->colour = colour;
}

bool Light::scatter(const Ray &incomingRay,
                     const HitRecord &rec,
                     Vector3 &attenuation,
                     Ray &scatteredRay) const
{
    return false;
}

Vector3 Light::emitted()
{
    return colour;
}

Vector3 reflect(const Vector3 &v, const Vector3 &n)
{
    return v - n*2*v.dot(n);
}

bool refract(Vector3 v, Vector3 n, float refractiveIndexFrom, float refractiveIndexTo, Vector3 &refracted, float &outgoingCosTheta)
{
    /*
     * Based on Snell's Law from
     * https://en.wikipedia.org/wiki/Snell's_law#Vector_form
     */

    float refractiveIndexRatio = refractiveIndexFrom / refractiveIndexTo;

    v = v.getUnitVector();
    n = n.getUnitVector(); //Just in case it isn't already a unit vector. This might be redundant
    float incomingCosTheta = -n.dot(v);

    float discriminant = 1.0 -
            refractiveIndexRatio*refractiveIndexRatio*
            (1-incomingCosTheta*incomingCosTheta);

    //In this case there will be total internal reflection (no refraction)
    if (discriminant <= 0)
    {
        return false;
    }

    outgoingCosTheta = sqrt(discriminant);
    refracted = refractiveIndexRatio*v +
            (refractiveIndexRatio*incomingCosTheta - outgoingCosTheta)*n;

    return true;
}

float getSchlickApproximation(float cosine, float refractiveIndexFrom, float refractiveIndexTo)
{
    float r0 = (refractiveIndexFrom-refractiveIndexTo) /
            (refractiveIndexFrom+refractiveIndexTo);
    r0 *= r0;
    return r0 + (1-r0)*pow((1-cosine), 5);
}
