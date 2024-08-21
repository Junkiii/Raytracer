#include <rt/materials/cooktorrance.h>

namespace rt {

    CookTorranceMaterial::CookTorranceMaterial(Texture* diffuse)
        : diffuse(diffuse)
    {
        
    }

    RGBColor CookTorranceMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
        float angle = fabs(dot(normal, inDir));
        return diffuse->getColor(texPoint) / pi * angle;
    }

    RGBColor CookTorranceMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
        return RGBColor(.0f, .0f, .0f);
    }

    Material::SampleReflectance CookTorranceMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
        NOT_IMPLEMENTED;
    }

    Material::Sampling CookTorranceMaterial::useSampling() const {
        return SAMPLING_SECONDARY;
    }

}