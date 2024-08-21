#ifndef CG1RAYTRACER_SOLIDS_TRIANGLE_HEADER
#define CG1RAYTRACER_SOLIDS_TRIANGLE_HEADER

#include <rt/solids/solid.h>
#include <core/random.h>

namespace rt {

/*
* Represents a triangle solid.
*/
class Triangle : public Solid {
public:
    Triangle() {}
    Triangle(Point vertices[3], CoordMapper* texMapper, Material* material);
    Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;

    Point getV1() const { return v1; }
    Point getV2() const { return v2; }
    Point getV3() const { return v3; }

protected:
    Point v1, v2, v3;
    Vector normal;

    BBox box;
};

}

#endif