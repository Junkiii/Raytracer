#ifndef CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/scalar.h>
#include <core/random.h>
#include <core/matrix.h>
#include <rt/ray.h>
#include <core/transformation.h>

namespace rt {

class Point;
class Vector;

/*
* Perspective camera with depth of field effect.
*/
class DOFPerspectiveCamera : public Camera {
public:
    DOFPerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle,
        float focalDistance,
        float apertureRadius
    );

    virtual Ray getPrimaryRay(float x, float y) const;

private:
    Point center;
    Vector forward;
    Vector up;
    float vOA;
    float hOA;
    float focalDistance;
    float apertureRadius;
    
    Vector x_span;
    Vector y_span;

    Matrix R;
};
}

#endif