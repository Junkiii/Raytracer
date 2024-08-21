#include <rt/cameras/orthographic.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
    : center(center), forward(forward.normalize()), up(up), scaleX(scaleX), scaleY(scaleY)
{
    /*
    * Precalculating the span vectors.
    */
    x_span = cross(this->forward, up).normalize() * scaleX / 2;
    y_span = cross(x_span, this->forward).normalize() * scaleY / 2;
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
    /*
    * Calculate the ray. Normalize!
    * (-DIFF-) no forward.normalize() here
    */
    return(Ray(center + x_span * x + y_span * y, forward));
}

}
