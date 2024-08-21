#include <rt/solids/triangle.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
    : Solid(texMapper, material), v1(vertices[0]), v2(vertices[1]), v3(vertices[3])
{
    /*
    * Precalculate the normal vector and the area.
    */
    normal = cross((v2 - v1), (v3 - v1)).normalize();
    area = cross((v1 - v2), (v1 - v3)).length() / 2;
    
    Point mi = min(min(v1, v2), v3);
    Point ma = max(max(v1, v2), v3);
    box = BBox(mi, ma);
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material)
    : Solid(texMapper, material), v1(v1), v2(v2), v3(v3)
{
    /*
    * Precalculate the normal vector and the area;
    */
    normal = cross((v2 - v1), (v3 - v1)).normalize();
    area = cross((v1 - v2), (v1 - v3)).length() / 2;

    Point mi = min(min(v1, v2), v3);
    Point ma = max(max(v1, v2), v3);
    box = BBox(mi, ma);
}

/**
* Returns the bounding box of the triangle.
* Could be precomputed. Is it worth ?
*/
BBox Triangle::getBounds() const {
    return box;
}

/**
* Intersection function of the triangle.
* Using barycentric coordinates.
*/
Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {
    Vector nab = cross(v2 - ray.o, v1 - ray.o);
    Vector nac = -cross(v3 - ray.o, v1 - ray.o);
    Vector nbc = cross(v3 - ray.o, v2 - ray.o);

    float dot1 = dot(ray.d, nab);
    float dot2 = dot(ray.d, nac);
    float dot3 = dot(ray.d, nbc);

    float denom = dot1 + dot2 + dot3;

    if (fequal(denom, 0.0f)) return Intersection::failure();

    float l3 = dot1 / (denom);
    float l2 = dot2 / (denom);
    float l1 = dot3 / (denom);

    if (l1 >= 0 && l2 >= 0 && l3 >= 0) {
        Point hitpoint = l1 * v1 - -l2 * v2 + l3 * v3;
        
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
        return Intersection(dist, ray, this, normal, Point(l1, l2, l3));
    }
    else {
        
        return Intersection::failure();
    }
   
}

/**
* Compute a random sample on the quad.
*/
Solid::Sample Triangle::sample() const {
    float r1 = random();
    float r2 = random(1.0f - r1);
    float r3 = 1.0f - r1 - r2;

    Point p = v1 * r1 + v2 * r2 + v3 * r3;
    Sample s;
    s.normal = normal;
    s.point = p;
    return s;
}

float Triangle::getArea() const {
    return area;
}

}