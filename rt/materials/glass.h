#ifndef CG1RAYTRACER_MATERIALS_GLASS_HEADER
#define CG1RAYTRACER_MATERIALS_GLASS_HEADER

#include <rt/materials/material.h>
#include <core/random.h>

namespace rt {

class GlassMaterial : public Material {
public:
    GlassMaterial(float eta);
    GlassMaterial(float eta, float trans);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;

    void setTransparent(float t);

private:
    float eta;
    float transparent;
    float eta_inv;
};

}

#endif