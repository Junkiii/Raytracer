#include <rt/integrators/raytrace.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
    Intersection intersection = world->scene->intersect(ray);
    RGBColor i(.0f, .0f, .0f);
    if (intersection) {
        Point local_ = intersection.solid->texMapper->getCoords(intersection);
        for (Light* light : world->light) {
            LightHit lighthit = light->getLightHit(intersection.hitPoint());
            float scale = lighthit.distance;
            if (lighthit.distance == FLT_MAX) {
                scale = 1;
            }
            Vector offset = 2500 * epsilon * intersection.normal() * scale;
            Ray shadowRay(intersection.hitPoint() + offset, lighthit.direction.normalize());
            float float1 = dot(intersection.normal(), ray.d);
            float float2 = dot(intersection.normal(), shadowRay.d);
            if ((float1 <= 0 && float2 >= 0) || (float1 >= 0 && float2 <= 0)) {
                Intersection intersectionShadow = world->scene->intersect(shadowRay);
                if (!intersectionShadow || (intersectionShadow.distance > lighthit.distance)) {
                    i = i + light->getIntensity(lighthit) * intersection.solid->material->getReflectance(local_, intersection.normal(), -ray.d, -shadowRay.d);
                }
            }
        }
        i = i + intersection.solid->material->getEmission(local_, intersection.normal(), -ray.d);
        return i;
    }
    return RGBColor(.0f, .0f, .0f);
}

}