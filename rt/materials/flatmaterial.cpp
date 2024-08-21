#include <rt/materials/flatmaterial.h>

namespace rt {

FlatMaterial::FlatMaterial(Texture* texture)
    :texture(texture)
{
    
}

RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    return RGBColor(.0f, .0f, .0f);
}

RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return texture->getColor(texPoint);
}

Material::SampleReflectance FlatMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return SampleReflectance(Vector(.0f, .0f, .0f), RGBColor(.0f, .0f, .0f));
}

Material::Sampling FlatMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}