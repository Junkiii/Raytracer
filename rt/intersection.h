#ifndef CG1RAYTRACER_INTERSECTION_HEADER
#define CG1RAYTRACER_INTERSECTION_HEADER

#include <core/scalar.h>
#include <core/vector.h>
#include <rt/ray.h>

namespace rt {

class Solid;

class Intersection {
public:
    Ray ray;
    const Solid* solid;
    float distance;

    Intersection() {}
    static Intersection failure();
    Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& uv);

    Point hitPoint() const;
    Vector normal() const;
    Point local() const;

    operator bool(); //this allows intersection object to be put directly in conditional statements. Becomes true iff there is an intersection

private:
    Vector _normal;
    Point _local;
    Point hit_point;

    // Variable to determine whether the intersection object is a real intersection or is not an intersection
    bool fail;
};

}

#endif