#include <rt/solids/skybox.h>

namespace rt {
    Skybox::Skybox(CoordMapper* texMapper, Material* material)
        : Solid(texMapper, material)
    {

    }

    BBox Skybox::getBounds() const {
        NOT_IMPLEMENTED;
    }

    Intersection Skybox::intersect(const Ray& ray, float previousBestDistance) const {
        return Intersection(FLT_MAX, ray, this, Vector::rep(FLT_MAX), Point::rep(FLT_MAX));
    }

    Solid::Sample Skybox::sample() const {
        NOT_IMPLEMENTED;
    }

    float Skybox::getArea() const {
        NOT_IMPLEMENTED;
    }
}
