#include <rt/integrators/recraytrace.h>

namespace rt {

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
    return getRadianceWrapper(ray, 0);
}

RGBColor RecursiveRayTracingIntegrator:: getRadianceWrapper(const Ray& ray, int counter) const {
    if (counter > depth_max) {
        return RGBColor(.0f, .0f, .0f);
    }
    counter++; 
    Intersection intersection = world->scene->intersect(ray);
    if (!intersection) return RGBColor(.0f, .0f, .0f);

    // only for debugging
    //if (intersection.solid->material == nullptr) return RGBColor::rep(0.0f);

    Material::Sampling sampling = intersection.solid->material->useSampling();

    if (sampling == Material::SAMPLING_NOT_NEEDED) {
        return normalGetRadiance(ray, intersection);
    }
    else if (sampling == Material::SAMPLING_ALL) {
        Material::SampleReflectance sr = intersection.solid->material->getSampleReflectance(intersection.solid->texMapper->getCoords(intersection), intersection.normal(), -ray.d);

        return getRadianceWrapper(Ray(intersection.hitPoint() + offset_scale * epsilon * sr.direction, sr.direction), counter) * sr.reflectance;
    }
    else {
        RGBColor normal = normalGetRadiance(ray, intersection);
        Material::SampleReflectance sr = intersection.solid->material->getSampleReflectance(intersection.solid->texMapper->getCoords(intersection), intersection.normal(), -ray.d);

        RGBColor secondaryColor = getRadianceWrapper(Ray(intersection.hitPoint() + offset_scale * epsilon * sr.direction, sr.direction), counter) * sr.reflectance;

        return normal + secondaryColor;
    }
    return RGBColor(.0f, .0f, .0f);
}

RGBColor RecursiveRayTracingIntegrator::normalGetRadiance(const Ray& ray, Intersection& intersection) const {
    RGBColor i(.0f, .0f, .0f);
    if (intersection) {
        for (Light* light : world->light) {
            LightHit lighthit = light->getLightHit(intersection.hitPoint());
            float scale = lighthit.distance;
            if (lighthit.distance == FLT_MAX) {
                scale = 1;
            }
            Vector offset = offset_scale * epsilon * intersection.normal() * scale;
            Ray shadowRay(intersection.hitPoint() + offset, lighthit.direction);
            float float1 = dot(intersection.normal(), ray.d);
            float float2 = dot(intersection.normal(), shadowRay.d);
            if (true /*(float1 <= 0 && float2 >= 0) || (float1 >= 0 && float2 <= 0)*/) {
                Intersection intersectionShadow = world->scene->intersect(shadowRay);
                if (!intersectionShadow || (intersectionShadow.distance > lighthit.distance - offset_scale * epsilon) || (intersectionShadow.solid->material->donot)) {
                    i = i + light->getIntensity(lighthit) * intersection.solid->material->getReflectance(intersection.solid->texMapper->getCoords(intersection), intersection.normal(), -ray.d, -shadowRay.d);
                }
            }
        }
        i = i + intersection.solid->material->getEmission(intersection.solid->texMapper->getCoords(intersection), intersection.normal(), -ray.d);
        return i;
    }
    return RGBColor(.0f, .0f, .0f);
}

}