#ifndef CG1RAYTRACER_COORDMAPPERS_WORLD_HEADER
#define CG1RAYTRACER_COORDMAPPERS_WORLD_HEADER

#include <rt/coordmappers/coordmapper.h>
#include <core/vector.h>
#include <rt/intersection.h>
#include <core/point.h>

namespace rt {

class Float4;

class WorldMapper : public CoordMapper {
public:
    WorldMapper();
    explicit WorldMapper(const Vector& scale);
    virtual Point getCoords(const Intersection& hit) const;
private:
    Vector scale;
};

}

#endif