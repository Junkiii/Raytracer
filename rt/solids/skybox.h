#ifndef CG1RAYTRACER_SOLIDS_SKYBOX_HEADER
#define CG1RAYTRACER_SOLIDS_SKYBOX_HEADER

#include <rt/solids/solid.h>

namespace rt {

    class Skybox : public Solid {
    public:
        Skybox() {}
        Skybox(CoordMapper* texMapper, Material* material);

        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
        virtual Sample sample() const;
        virtual float getArea() const;

    };

}

#endif