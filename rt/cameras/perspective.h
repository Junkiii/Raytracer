#ifndef CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/scalar.h>

namespace rt {

/*
* Perspective camera.
* Rays have the same origin.
*/
class PerspectiveCamera : public Camera {
public:
    Point center;
    Vector forward;
    Vector up;
    float vOA;
    float hOA;
    
    PerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle
        );

    virtual Ray getPrimaryRay(float x, float y) const;

private:
    Vector x_span;
    Vector y_span;
};
}

#endif