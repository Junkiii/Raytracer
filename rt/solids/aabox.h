#ifndef CG1RAYTRACER_SOLIDS_BOX_HEADER
#define CG1RAYTRACER_SOLIDS_BOX_HEADER

#include <rt/solids/solid.h>
#include <rt/solids/infiniteplane.h>

namespace rt {

/*
* Represents an axis aligned box solid.
*/
class AABox : public Solid {
public:
    AABox() {}
    AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;
private:
    Point corner1, corner2;
    Point ma, mi;
};

}

#endif