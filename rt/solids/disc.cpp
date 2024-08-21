#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
    : Solid(texMapper, material), center(center), normal(normal.normalize()), radius(radius) 
{
    area = pi * radius * radius;
}

/**
* Returns the bounding box of the disc.
* Could be precomputed. Is it worth ?
*/
BBox Disc::getBounds() const {
    float x = radius * sqrt(1 - normal.x * normal.x);
    float y = radius * sqrt(1 - normal.y * normal.y);
    float z = radius * sqrt(1 - normal.z * normal.z);

    Vector maxV = center - Point(x, y, z);
    Vector minV = center - Point(-x, -y, -z);

    return BBox(Point(maxV.x, maxV.y, maxV.z), Point(-minV.x, -minV.y, -minV.z));
}

/**
* Intersection function for the disc solid.
*/
Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection intersection;

    float denominator = dot(normal, ray.d);
    float numerator = dot((center - ray.o), normal);

    if (fequal(denominator, .0f)) { // plane and ray are parallel
        if (fequal(numerator, .0f)) { // ray is contained in the plane
            intersection = Intersection::failure(); // TODO: check this! 
        }
        else { // ray is not contained in the plane
            intersection = Intersection::failure();
        }
    }
    else {
        float dist = numerator / denominator;
        intersection =  Intersection(dist, ray, this, normal, ray.getPoint(dist));
        if ((center - ray.getPoint(dist)).lensqr() > (sqr(radius))) {
            intersection = Intersection::failure();
        }
    }
    if (previousBestDistance < (numerator/denominator)) return Intersection::failure();
    return intersection;

    
}

Solid::Sample Disc::sample() const {
    NOT_IMPLEMENTED;
}

float Disc::getArea() const {
    return area;
}

}
