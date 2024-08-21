#include <rt/lights/spotlight.h>

namespace rt {

    SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity)
        : PointLight(position, intensity), direction(direction), angle(angle), exp(power)
{
    
}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
    float light_angle = -dot(irr.direction.normalize(), direction.normalize());
    if (acos(light_angle) <= angle) {
        RGBColor temp = (pow(light_angle, exp) / (irr.distance * irr.distance)) * intensity;
        return temp;
    }
    return RGBColor(.0f, .0f, .0f);
}

}
