#include <rt/materials/phong.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
    : specular(specular), exponent(exponent)
{
    
}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    float dot_ = dot(inDir, normal);
    Vector reversed_inDir = -inDir + 2 * dot_ * normal;

    RGBColor reflect = specular->getColor(texPoint) * powf(max(0.0f, dot(reversed_inDir, -outDir)), exponent) * fabs(dot_) * (exponent + 2) * 0.5 * pi_inv;
    return reflect;
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor(.0f, .0f, .0f);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return SampleReflectance(Vector(.0f, .0f, .0f), RGBColor(.0f, .0f, .0f));
}

Material::Sampling PhongMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}