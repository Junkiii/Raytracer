#include <rt/cameras/dofperspective.h>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius)
    : center(center), forward(forward.normalize()), up(up), vOA(verticalOpeningAngle), hOA(horizontalOpeningAngle), focalDistance(focalDistance), apertureRadius(apertureRadius)
{
    /*
    * (-DIFF-) no forward.normalize() here.
    */
    /*
    * Precalculating the span vectors,
    * focal point
    */
    x_span = cross(forward, up).normalize() * tan(hOA / 2);
    y_span = cross(x_span, forward).normalize() * tan(vOA / 2); 
}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
    /*
    * Calculating the standard perspective camera ray.
    */
    Ray ray = Ray(center, (forward + x_span * x + y_span * y)/*.normalize()*/);

    /*
    * Creating a random radius and a random theta.
    * sqrt(random()) to prevent clustering around the center of the circle
    */
    float radius = apertureRadius * sqrt(random());
    float theta = 2.0f * pi * random();

    /*
    * Calculating the a span vector of the sampling disc,
    * the focal point,
    * and the random rotation matrix with axis ray.d and random theta.
    */
    Vector span = cross(cross(up, ray.d), ray.d);
    Point focal_point = center + ray.d * focalDistance;
    Matrix transformation = rotation(ray.d, theta);

    /*
    * Rotating the span vector with the rotation matrix
    * and scaling it with the random radius.
    */
    span = (transformation * span).normalize() * radius;

    /*
    * Calculating the new ray with the new center and the new direction
    */
    Point new_center = center + span;
    Vector new_dir = (focal_point - new_center).normalize();
    return Ray(new_center, new_dir);
}

}