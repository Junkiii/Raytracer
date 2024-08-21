#include <rt/materials/glass.h>

namespace rt {

GlassMaterial::GlassMaterial(float eta)
    : eta(eta), eta_inv(1.0f / eta), transparent(0.5f) {}

GlassMaterial::GlassMaterial(float eta, float trans)
    : eta(eta), eta_inv(1.0f / eta), transparent(trans) {}

RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    // Because of performance reasons, it is smarter and easier to 
    // calculate everything in the getSampleReflectance() function.
    // This function should never be called!
    
    return RGBColor::rep(.0f);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(.0f);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    float eta_t = eta;

    Vector normal_corr = normal;

    // Swap normal vector and eta if inside medium
    float cos_theta_i = dot(outDir, normal_corr);
    if (cos_theta_i < 0.0f) {
        eta_t = eta_inv;
        normal_corr = -normal_corr;
    }


    cos_theta_i = dot(outDir.normalize(), normal_corr);
    float sin_theta_i = sqrt(max(0.0f, 1.0f - sqr(cos_theta_i)));
    float sin_theta_t = sin_theta_i / eta_t;

    //LOOK AT THIS

    float cos_theta_t;
    float fresnel;

    if (sin_theta_t > 1) { // total internal reflection ( critical angle )
        cos_theta_t = -cos_theta_i;
        sin_theta_t = sin_theta_i;
        fresnel = 1;
    }
    else {
        cos_theta_t = sqrt(max(0.0f, 1 - sqr(sin_theta_t)));

        float r_par = ((eta_t * cos_theta_i) - (cos_theta_t)) /
            ((eta_t * cos_theta_i) + (cos_theta_t));
        float r_per = (( cos_theta_i)-(eta_t * cos_theta_t)) /
            ((cos_theta_i)+(eta_t * cos_theta_t));

        // Fresnel term
        fresnel = 0.5f * (sqr(r_par) + sqr(r_per));

        // Choose a random number to decide if you want to sample reflection or transmission
        float r = random();

        if (r < transparent) {     // 50% sample mirror
            cos_theta_t = -cos_theta_i;
            sin_theta_t = sin_theta_i;
            fresnel = (2.0f * fresnel);
        }
        else {             // 50% sample transmission
            fresnel = (2.0f * (1.0f - fresnel) / sqr(eta_t));
        }
    }


    Vector direction;
    RGBColor value = RGBColor::rep(fresnel);

    direction = (outDir - dot(outDir, normal_corr) * normal_corr).normalize();
    direction = -cos_theta_t * normal_corr - sin_theta_t * direction;

    return SampleReflectance(direction.normalize(), value);
}

Material::Sampling GlassMaterial::useSampling() const {
    return SAMPLING_ALL;
}

void GlassMaterial::setTransparent(float t) {
    transparent = t;
}

}