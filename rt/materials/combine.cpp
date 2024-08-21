#include <rt/materials/combine.h>

namespace rt {

CombineMaterial::CombineMaterial()
{
    /* TODO */
}

void CombineMaterial::add(Material* m, float w) {
    CMaterial cmat;
    cmat.material = m;
    cmat.weight = w;
    materials.push_back(cmat);
}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    RGBColor reflect(.0f, .0f, .0f);
    for (const CMaterial& mat : materials) {
        if (mat.material->useSampling() == SAMPLING_NOT_NEEDED) {
            reflect = reflect + mat.material->getReflectance(texPoint, normal, outDir, inDir) * mat.weight;
        }
    }
    return reflect;
}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    RGBColor reflect(.0f, .0f, .0f);
    for (const CMaterial& mat : materials) {
        reflect = reflect + mat.material->getEmission(texPoint, normal, outDir) * mat.weight;
    }
    return reflect;
}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    Vector reversed_out = -outDir + 2 * dot(outDir, normal) * normal;
    RGBColor reflect(.0f, .0f, .0f);
    for (const CMaterial& mat : materials) {
        reflect = reflect + mat.material->getSampleReflectance(texPoint, normal, outDir).reflectance * mat.weight;
    }
    return SampleReflectance(reversed_out, reflect);
}

Material::Sampling CombineMaterial::useSampling() const {
    return SAMPLING_SECONDARY;
}

}