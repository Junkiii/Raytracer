#ifndef CG1RAYTRACER_MATERIALS_PHONG_HEADER
#define CG1RAYTRACER_MATERIALS_PHONG_HEADER

#include <rt/materials/material.h>
#include <rt/textures/texture.h>

namespace rt {

    class Texture;

    class CookTorranceMaterial : public Material {
    public:
        CookTorranceMaterial(Texture* diffuse);
        virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
        virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
        virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
        virtual Sampling useSampling() const;
    private:
        Texture* diffuse;
    };

}

#endif