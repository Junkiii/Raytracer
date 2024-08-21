#ifndef CG1RAYTRACER_PRIMMOD_BMAP_HEADER
#define CG1RAYTRACER_PRIMMOD_BMAP_HEADER

#include <rt/primitive.h>
#include <rt/solids/triangle.h>
#include <rt/textures/texture.h>
#include <rt/intersection.h>
#include <core/matrix.h>
#include <rt/coordmappers/tmapper.h>

namespace rt {

class Triangle;
class Texture;

class BumpMapper : public Primitive {
public:
    BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale);
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
private:
    Point bv1;
    Point bv2;
    Point bv3;
    float vscale;
    Triangle* base;
    Texture* bumpmap;

    Vector w_x;
    Vector w_y;
    float sign;
};

}

#endif