#include <rt/materials/fuzzymirror.h>

namespace rt {

    FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
        : eta(eta), kappa(kappa), fuzzyangle(fuzzyangle)
{
    
}

RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    float cos_theta_i = fabs(dot(inDir, normal));
    float r_par = ((eta * eta + kappa * kappa) * cos_theta_i * cos_theta_i - 2 * eta * cos_theta_i + 1) / ((eta * eta + kappa * kappa) * cos_theta_i * cos_theta_i + 2 * eta * cos_theta_i + 1);
    float r_per = ((eta * eta + kappa * kappa) - 2 * eta * cos_theta_i + cos_theta_i * cos_theta_i) / ((eta * eta + kappa * kappa) + 2 * eta * cos_theta_i + cos_theta_i * cos_theta_i);

    float F_r = 0.5f * (r_par + r_per);
    float value = F_r;
    return RGBColor(value, value, value);
}

RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor(.0f, .0f, .0f);
}

Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    Vector reversed_out = -outDir + 2 * dot(outDir, normal) * normal;

    float r1 = random();
    float r2 = sqrt(random());


    float radius =  tan(fuzzyangle) * r2;
    float theta =  2.0f * pi * r1;

    Vector span = cross(cross(normal, reversed_out), reversed_out);
    
    Vector nnaxis = reversed_out;

    Vector r = nnaxis.normalize();
    int min_r = r.minCompAbs();
    Vector s_;
    if (min_r == 0) s_ = Vector(0, -r.z, r.y);
    else if (min_r == 1) s_ = Vector(-r.z, 0, r.x);
    else s_ = Vector(-r.y, r.x, 0);
    Vector s = s_.normalize();
    Vector t = cross(r, s);

    Matrix M = Matrix::identity();
    M.r1.x = r.x;
    M.r1.y = s.x;
    M.r1.z = t.x;

    M.r2.x = r.y;
    M.r2.y = s.y;
    M.r2.z = t.y;

    M.r3.x = r.z;
    M.r3.y = s.z;
    M.r3.z = t.z;

    Matrix R = Matrix::identity();
    R.r2.y = cos(theta);
    R.r2.z = -sin(theta);
    R.r3.y = sin(theta);
    R.r3.z = cos(theta);

    Matrix transformation = product(product(M, R), M.transpose());
    

    Vector span_rot = transformation * span;
    span_rot = span_rot.normalize();
    span_rot = span_rot * radius;

    Vector random_dir = (texPoint + reversed_out.normalize() + span_rot) - texPoint;

    SampleReflectance sr(random_dir, getReflectance(texPoint, normal, outDir, random_dir));
    return sr;
}

Material::Sampling FuzzyMirrorMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}
