#include <rt/coordmappers/environmentmapper.h>

namespace rt {

    Point EnvironmentMapper::getCoords(const Intersection& hit) const {
        return Point(hit.ray.d.x, hit.ray.d.y, hit.ray.d.z);
    }

    EnvironmentMapper::EnvironmentMapper(int placeholder)
    {
        
    }

    EnvironmentMapper::EnvironmentMapper()
    {

    }

}