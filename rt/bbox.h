#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>
#include <cfloat> // i dont know if this is correct here
#include <rt/ray.h>

namespace rt {

/*
* Represents an axis-aligned bounding box.
* Defined by a Point min and a Point max.
*/
class BBox {
public:
    Point min, max;

    BBox() {}
    BBox(const Point& min, const Point& max) : min(min), max(max), unbound(false) {}
    BBox(const Point& min, const Point& max, bool unbound) : min(min), max(max), unbound(unbound) {}

    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    inline Vector diagonal() const { return max - min; }

    float area() const {
        Vector diff = max - min;
        return diff.x * diff.y * diff.z;
    }

    std::pair<float, float> intersect(const Ray& ray) const;

    bool isUnbound();

private:
    /*
    * Bool value if the bounding box is unlimited in any direction.
    */
    bool unbound;
};

}

#endif