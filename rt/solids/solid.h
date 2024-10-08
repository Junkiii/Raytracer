#ifndef CG1RAYTRACER_SOLIDS_SOLID_HEADER
#define CG1RAYTRACER_SOLIDS_SOLID_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/primitive.h>
#include <rt/coordmappers/world.h>

namespace rt {

class Material;
class CoordMapper;

/*
A solid is a physical primitive that has material and can be textured
*/
class Solid : public Primitive {
public:
    struct Sample {
        Point point;
        Vector normal;
        //Sample(const Point& point, const Vector& vector) : point(point), normal(normal) {};
    };

    Material* material;
    CoordMapper* texMapper;
    explicit Solid(CoordMapper* texMapper = nullptr, Material* material = nullptr);
    virtual Sample sample() const = 0;
    virtual float getArea() const = 0;
    virtual void setMaterial(Material* m) { material = m; }
    virtual void setCoordMapper(CoordMapper* cm) { texMapper = cm; }

protected:
    float area;
};

}


#endif