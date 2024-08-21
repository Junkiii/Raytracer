#include <rt/materials/lambertian.h>

namespace rt {

LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse)
    : emission(emission), diffuse(diffuse)
{
    
}

RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    float angle = fabs(dot(normal, inDir));
    return diffuse->getColor(texPoint) / pi * angle;
}

RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    
    return emission->getColor(texPoint);
}

Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return SampleReflectance(Vector(.0f, .0f, .0f), RGBColor(.0f, .0f, .0f));
}

Material::Sampling LambertianMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}