#ifndef CG1RAYTRACER_SOLIDS_QUADRIC_HEADER
#define CG1RAYTRACER_SOLIDS_QUADRIC_HEADER

#include <rt/solids/solid.h>

namespace rt {

    /*
    * Represents a quadris solid.
    */
    class Quadric : public Solid {
    public:
        Quadric() {}
        Quadric(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, CoordMapper* texMapper, Material* material);

        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
        virtual Sample sample() const;
        virtual float getArea() const;
        Vector calculate_normal(Point hitpoint, Ray ray) const;

    private:
        float a, b, c, d, e, f, g, h, i, j; 
    };
}

#endif