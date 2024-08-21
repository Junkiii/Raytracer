#include <rt/solids/sphere.h>

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
    : Quadric(1, 1, 1, 0, 0, 0, -2*center.x, -2*center.y, -2*center.z, center.x*center.x + center.y*center.y + center.z*center.z - radius*radius, texMapper, material), radius(radius), center(center) 
{
    area = 4 * pi * radius * radius;
}

/**
* Returns the bounding box of the sphere.
* Could be precomputed. Is it worth ?
*/
BBox Sphere::getBounds() const {
        return BBox(Point(center.x - radius, center.y - radius, center.z - radius), Point(center.x + radius, center.y + radius, center.z + radius));
}

/**
* Intersection function for the sphere is just a quadric intersection.
*/
Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
    return Quadric::intersect(ray, previousBestDistance);
}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    return area;
}

}
