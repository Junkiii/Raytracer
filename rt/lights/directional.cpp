#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {

    DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
        :direction(direction), intensity(color)
{
    
}

LightHit DirectionalLight::getLightHit(const Point& p) const {
    LightHit temp;
    temp.distance = FLT_MAX;
    temp.direction = -direction;
    return temp;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
    return intensity;
}

}
