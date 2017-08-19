#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "surface.hpp"

Vector3 reflect(const Vector3 &v, const Vector3 &n);
bool refract(Vector3 v, Vector3 n, float refractiveIndexFrom, float refractiveIndexTo, Vector3 &refracted, float &outgoingCosTheta);
float getSchlickApproximation(float cosine, float refractiveIndexFrom, float refractiveIndexTo);

class Material
{
    public:
        /**
         * @brief scatter Determines if an incoming ray should be scattered
         * upon hitting the Material
         * @param incomingRay The incoming ray that will hit the Material
         * @param rec The HitRecord containing information about the ray hit
         * @param attenuation
         * @param scatteredRay The scattered ray
         * @return
         */
        virtual bool scatter(const Ray &incomingRay,
                             const HitRecord &rec,
                             Vector3 &attenuation,
                             Ray &scatteredRay) const = 0;

        virtual Vector3 emitted();
};

class Diffuse : public Material
{
    public:
        //Constructors
        Diffuse(const Vector3 &albedo);

        //Methods
        virtual bool scatter(const Ray &incomingRay,
                             const HitRecord &rec,
                             Vector3 &attenuation,
                             Ray &scatteredRay) const;

    private:
        Vector3 albedo;
};

class Metal : public Material
{
    public:
        Metal(const Vector3 &albedo);
        Metal(const Vector3 &albedo, float fuzz);

        virtual bool scatter(const Ray &incomingRay,
                             const HitRecord &rec,
                             Vector3 &attenuation,
                             Ray &scatteredRay) const;

    private:
        Vector3 albedo;
        float fuzz;
};

class Dielectric : public Material
{
    public:
        Dielectric(float refractiveIndex);

        virtual bool scatter(const Ray &incomingRay,
                             const HitRecord &rec,
                             Vector3 &attenuation,
                             Ray &scatteredRay) const;

    private:
        float refractiveIndex;
};

class Light : public Material
{
    public:
        Light();
        Light(const Vector3 &colour);

        virtual bool scatter(const Ray &incomingRay,
                             const HitRecord &rec,
                             Vector3 &attenuation,
                             Ray &scatteredRay) const;
        virtual Vector3 emitted();

    private:
        Vector3 colour;

};

#endif // MATERIAL_HPP
