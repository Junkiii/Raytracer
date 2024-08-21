#include <rt/materials/mirror.h>
#include <core/scalar.h>

namespace rt {

MirrorMaterial::MirrorMaterial(float eta, float kappa)
    : eta(eta), kappa(kappa)
{
    precalc = eta * eta + kappa * kappa;
}

RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    float cos_theta_i = fabs(dot(inDir, normal));
    float r_par = (precalc * cos_theta_i * cos_theta_i - 2 * eta * cos_theta_i + 1) / (precalc * cos_theta_i * cos_theta_i + 2 * eta * cos_theta_i + 1);
    float r_per = (precalc - 2 * eta * cos_theta_i + cos_theta_i * cos_theta_i) / (precalc + 2 * eta * cos_theta_i + cos_theta_i * cos_theta_i);

    float F_r = 0.5f * (r_par + r_per);
    float value = F_r;
    return RGBColor(value, value, value);
}

RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor(.0f, .0f, .0f);
}

Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    Vector reversed_out = -outDir + 2 * dot(outDir, normal) * normal;
    return SampleReflectance(reversed_out, getReflectance(texPoint, normal, outDir, reversed_out));
}

Material::Sampling MirrorMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}