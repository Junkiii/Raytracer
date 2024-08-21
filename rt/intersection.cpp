#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
    : distance(distance), ray(ray), solid(solid), _normal(normal), _local(local), fail(distance <= 0)
{
    /*
    * Precalculating the hitPoint.
    * IMPORTANT: distance and ray should NOT change!
    */
    //hit_point = ray.getPoint(distance);
}

Intersection::operator bool() {
    return !fail;
}

Intersection Intersection::failure() {
    Intersection f;
    f.fail = true;
    return f;
}

/**
* Return the hitPoint.
* Either calculate with ray.getPoint(distance) or precalculate.
* (-DIFF-)
*/
Point Intersection::hitPoint() const {
    //return hit_point;
    return ray.getPoint(distance);
}

Vector Intersection::normal() const {
    return _normal;
}

Point Intersection::local() const {
    return _local;
}

}
