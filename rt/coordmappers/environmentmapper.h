#ifndef CG1RAYTRACER_COORDMAPPERS_ENVIRONMENT_HEADER
#define CG1RAYTRACER_COORDMAPPERS_ENVIRONMENT_HEADER

#include <rt/coordmappers/coordmapper.h>
#include <core/vector.h>
#include <rt/intersection.h>
#include <core/point.h>

namespace rt {

    class Float4;

    class EnvironmentMapper : public CoordMapper {
    public:
        EnvironmentMapper();
        explicit EnvironmentMapper(int placeholder);
        virtual Point getCoords(const Intersection& hit) const;
    
    };

}

#endif