#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
    : Solid(texMapper, material), corner1(corner1), corner2(corner2) 
{
    ma = max(corner1, corner2);
    mi = min(corner1, corner2);
    Vector diff = ma - mi;
    area = diff.x * diff.y * diff.z;
}

BBox AABox::getBounds() const {
    return BBox(min(corner1, corner2), max(corner1, corner2));
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    
    return area;
}

/**
* Intersection function for the AABox solid.
*/
Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
    /*
    * (-DIFF-) ma and mi precalculated
    */
    /*
    * Calculating t_near and t_far and compute intersection.
    */
    Vector t_min = (mi - ray.o) / ray.d;
    Vector t_max = (ma - ray.o) / ray.d;

    Vector t_near = min(t_min, t_max);
    Vector t_far = max(t_min, t_max);

    int max_ind = t_near.maxComp();
    float minfar = min(t_far.x, t_far.y, t_far.z);

    Vector normal(0, 0, 0);
    normal[max_ind] = 1.0f;
    normal[max_ind] = copysignf(1.0f, -dot(normal, ray.d));

    if (t_near[max_ind] < minfar) { // intersection
        if (previousBestDistance < t_near[max_ind]) return Intersection::failure();
        return Intersection(t_near[max_ind], ray, this, normal, ray.getPoint(t_near[max_ind]));
    }
    else { // no intersection
        return Intersection::failure();
    }
}
}
