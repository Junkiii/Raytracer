#ifndef CG1RAYTRACER_CAMERAS_ORTHOGRAPHIC_HEADER
#define CG1RAYTRACER_CAMERAS_ORTHOGRAPHIC_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <rt/ray.h>

namespace rt {

/*
* Orthographic camera.
* Rays are parallel.
*/
class OrthographicCamera : public Camera {
public:
    Point center;
    Vector forward;
    Vector up;
    float scaleX;
    float scaleY;

    OrthographicCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float scaleX,
        float scaleY
        );

    virtual Ray getPrimaryRay(float x, float y) const;

private:
    Vector x_span;
    Vector y_span;
};
}

#endif