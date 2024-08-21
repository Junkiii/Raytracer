#include <rt/ray.h>

namespace rt {

Ray::Ray(const Point& o, const Vector& d)
    : o(o), d(d) {}

/**
* Returns the point on the ray with given 
* distance form the origin.
*/
Point Ray::getPoint(float distance) const {
    return d * distance + o;
}

}
