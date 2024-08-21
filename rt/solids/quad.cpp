#include <rt/solids/quad.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
    : Solid(texMapper, material), origin(origin), span1(span1), span2(span2) 
{
    normal = cross((origin + span1 - origin), (origin + span2 - origin)).normalize();
    area = cross(span1, span2).length();
    
    Point p1 = origin;
    Point p2 = origin + span1 + span2;

    p1 = min(p1, p2);
    p2 = max(p1, p2);

    box = BBox(p1, p2);
}

/**
* Returns the bounding box of the quad.
* Could be precomputed. Is it worth ?
*/
BBox Quad::getBounds() const {
    return box;
}

/**
* Intersection function of the quad.
* Using barycentric coordinates.
* (-DIFF-) Improved Performance
*/
Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {
    Vector nab = cross(origin + span1 - ray.o, origin - ray.o);
    Vector nac = -cross(origin + span2 - ray.o, origin - ray.o);
    Vector nbc = cross(origin + span2 - ray.o, origin + span1 - ray.o);

    float dot1 = dot(ray.d, nab);
    float dot2 = dot(ray.d, nac);
    float dot3 = dot(ray.d, nbc);
    float dot_sum = dot1 + dot2 + dot3;

    if (fequal(dot_sum, 0.0f)) return Intersection::failure();

    float l3 = dot1 / dot_sum;
    float l2 = dot2 / dot_sum;
    float l1 = dot3 / dot_sum;

    if (l2 > 0 && l3 > 0 && l2 < 1 && l3 < 1) {
        Point hitpoint = origin + l2 * span1 + l3 * span2;
        
        float dist;

        if (!fequal(ray.d.x, 0.0f)) {
            dist = (hitpoint.x - ray.o.x) / ray.d.x;
        }
        else if (!fequal(ray.d.y, 0.0f)) {
            dist = (hitpoint.y - ray.o.y) / ray.d.y;
        }
        else {
            dist = (hitpoint.z - ray.o.z) / ray.d.z;
        }
        if (previousBestDistance < dist) return Intersection::failure();
        return Intersection(dist, ray, this, normal, Point(l2, l3, .0f));
    }
    else {
        return Intersection::failure();
    }
}

/**
* Compute a random sample on the quad.
*/
Solid::Sample Quad::sample() const {
    Point p = origin + span1 * random() + span2 * random();
    Sample s;
    s.normal = normal;
    s.point = p;
    return s;
}

float Quad::getArea() const {
    return area;
}

}
