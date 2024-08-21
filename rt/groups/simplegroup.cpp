#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    Point mi(FLT_MAX, FLT_MAX, FLT_MAX);
    Point ma(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (Primitive* p : primitives)
    {
        mi = min(p->getBounds().min, mi);
        ma = max(p->getBounds().max, ma);
    }
    return BBox(mi, ma);
}

Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {
    float pBD = previousBestDistance;
    Intersection i = Intersection::failure();
    for (Primitive* p : primitives)
    {
        Intersection curr = p->intersect(ray, pBD);
        if (curr) {
            if (curr.distance < pBD) {
                i = curr;
                pBD = curr.distance;
            }
        }
    }
    return i;
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
    primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    for (Primitive* p : primitives) {
        p->setMaterial(m);
    }
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    for (Primitive* p : primitives) {
        p->setCoordMapper(cm);
    }
}

}
