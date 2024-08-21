#include <rt/cameras/perspective.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
    : center(center), forward(forward.normalize()), up(up), vOA(verticalOpeningAngle), hOA(horizontalOpeningAngle)
{
    /*
    * Precalculating the span vectors.
    */
    x_span = cross(forward, up).normalize() * tan(hOA / 2);
    y_span = cross(x_span, forward).normalize() * tan(vOA / 2);
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    /*
    * Calculate the ray. Normalize!
    */
    return Ray(center, (forward + x_span * x + y_span * y).normalize());
}

}