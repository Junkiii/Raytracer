#include <rt/coordmappers/world.h>

namespace rt {

Point WorldMapper::getCoords(const Intersection& hit) const {
    float x = hit.hitPoint().x * scale.x;
    float y = hit.hitPoint().y * scale.y;
    float z = hit.hitPoint().z * scale.z;
    return Point(x, y, z);
}

WorldMapper::WorldMapper()
{
    scale = Vector::rep(1.0f);
}

WorldMapper::WorldMapper(const Vector& scale)
    : scale(scale)
{
    
}

}