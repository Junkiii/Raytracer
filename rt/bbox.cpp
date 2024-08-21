#include <rt/bbox.h>

namespace rt {

/**
* Creating an empty bounding box.
* You can NOT intersect with this box.
*/
BBox BBox::empty() {
    Point max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    Point min(FLT_MAX, FLT_MAX, FLT_MAX);
    BBox fullbox(min, max);
    return fullbox;
}

/**
* Creating a bounding box spanning the whole space.
* You ALWAYS intersect with this box.
* unbound = true (in every direction)
*/
BBox BBox::full() {
    Point min(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    Point max(FLT_MAX, FLT_MAX, FLT_MAX);
    BBox fullbox(min, max);
    fullbox.unbound = true;
    return fullbox;
}

/**
* Extend the bounding box with a point.
* Update min and max.
*/
void BBox::extend(const Point& point) {
    min = rt::min(point, min);
    max = rt::max(point, max);
}

/**
* Extend the bounding box with a box.
* Update min and max.
*/
void BBox::extend(const BBox& bbox) {
    min = rt::min(bbox.min, min);
    max = rt::max(bbox.max, max);
}

/**
* Intersection function for the axis aligned bounding box.
*/
std::pair<float, float> BBox::intersect(const Ray& ray) const {
    /*
    * Calculating t_near and t_far and returning them as a pair.
    */
    Vector t_min = (min - ray.o) / ray.d;
    Vector t_max = (max - ray.o) / ray.d;
    
    Vector t_near = rt::min(t_min, t_max);
    Vector t_far = rt::max(t_min, t_max);

    int minInd = t_far.minComp();
    int maxInd = t_near.maxComp();
    
    float t1 = t_near[maxInd];
    float t2 = t_far[minInd];

    return { t1, t2 };
}

bool BBox::isUnbound() {
    return unbound;
}

}