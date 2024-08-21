#include <rt/lights/arealight.h>

#include <core/color.h>

namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    Solid::Sample s = source->sample();
    LightHit lighthit;
    lighthit.direction = s.point - p;
    lighthit.distance = lighthit.direction.length();
    lighthit.direction = lighthit.direction / lighthit.distance;
    lighthit.normal = s.normal;
    return lighthit;
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    float angle = fabs(dot(irr.normal, irr.direction));
    return source->material->getEmission(Point::rep(0.5f), irr.normal, irr.direction) * source->getArea() * angle / (irr.distance * irr.distance);
}

AreaLight::AreaLight(Solid* source)
    : source(source)
{
    
}

}