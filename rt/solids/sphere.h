#ifndef CG1RAYTRACER_SOLIDS_SPHERE_HEADER
#define CG1RAYTRACER_SOLIDS_SPHERE_HEADER

#include <rt/solids/solid.h>
#include <rt/solids/quadric.h>

namespace rt {

/**
* A sphere is just a quadric with the correct params.
*/
class Sphere : public Quadric {
public:
    Sphere() {}
    Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;

private:
    float radius;
    Point center;
};

}


#endif