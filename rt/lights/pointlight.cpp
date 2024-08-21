#include <rt/lights/pointlight.h>

#include <core/vector.h>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity)
    : position(position), intensity(intensity)
{
    
}

LightHit PointLight::getLightHit(const Point& p) const {
    LightHit temp;
    temp.direction = position - p;
    temp.distance = temp.direction.length();
    return temp;
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
    RGBColor temp = intensity / (irr.distance * irr.distance);
    return temp;
}

}
