#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material) 
    : Solid(texMapper, material), origin(origin), normal(normal) 
{
    area = FLT_MAX;
}

/**
* Returns the bounding box of the infinite plane.
* Could be precomputed. Is it worth ?
*/
BBox InfinitePlane::getBounds() const {
    if (fequal(dot(normal, Vector(1, 0, 0)), .0f)) { // y,z-plane
        return BBox(Point(origin.x, -FLT_MAX, -FLT_MAX), Point(origin.x, FLT_MAX, FLT_MAX), true);
    }
    else if (fequal(dot(normal, Vector(0, 1, 0)), .0f)) { // x,z-plane
        return BBox(Point(-FLT_MAX, origin.y, -FLT_MAX), Point(FLT_MAX, origin.y, FLT_MAX), true);
    }
    else if (fequal(dot(normal, Vector(0, 0, 1)), .0f)) { // x,y-plane
        return BBox(Point(-FLT_MAX, -FLT_MAX, origin.z), Point(FLT_MAX, FLT_MAX, origin.z), true);
    }
    else { // no plane --> unbound in every direction
        return BBox(Point(-FLT_MAX, -FLT_MAX, -FLT_MAX), Point(FLT_MAX, FLT_MAX, FLT_MAX), true);
    }
}

/**
* Intersection function for the infinite plane.
*/
Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
    float denominator = dot(normal, ray.d);
    float numerator = dot((origin - ray.o), normal);
    if (fequal(denominator, .0f)) { // plane and ray are parallel
        if (fequal(numerator, .0f)) { // ray is contained in the plane
            return Intersection::failure(); // TODO: check this! 
        }
        else { // ray is not contained in the plane
            return Intersection::failure();
        }
    }
    else {
        float dist = numerator / denominator;
        if (previousBestDistance < dist) return Intersection::failure();
        return Intersection(dist, ray, this, normal, ray.getPoint(dist));
    }
}

Solid::Sample InfinitePlane::sample() const {
    NOT_IMPLEMENTED;
}

float InfinitePlane::getArea() const {
    return area;
}

}
