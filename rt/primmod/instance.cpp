#include <rt/primmod/instance.h>

namespace rt {

Instance::Instance(Primitive* content) 
    : content_(content), transformation(Matrix::identity()), transformation_inv(Matrix::identity()) {}

Primitive* Instance::content() {
    return content_;
}

void Instance::reset() {
    transformation = Matrix::identity();
    transformation_inv = Matrix::identity();
}

/**
* Adding a translation to the total transformation.
* Update inverse.
*/
void Instance::translate(const Vector& t) {
    transformation = product(translation(t), transformation);
    transformation_inv = transformation.invert();
}

/**
* Adding a rotation to the total transformation.
* Update inverse.
*/
void Instance::rotate(const Vector& nnaxis, float angle) {
    transformation = product(rotation(nnaxis, angle), transformation);
    transformation_inv = transformation.invert();
}

/**
* Adding a scaling to the total transformation.
* Update inverse.
*/
void Instance::scale(float f) {
    transformation = product(scaling(f), transformation);
    transformation_inv = transformation.invert();
}

/**
* Adding a scaling to the total transformation.
* Update inverse.
*/
void Instance::scale(const Vector& s) {
    transformation = product(scaling(s), transformation);
    transformation_inv = transformation.invert();
}

void Instance::setMaterial(Material* m) {
    content_->setMaterial(m);
}

void Instance::setCoordMapper(CoordMapper* cm) {
    content_->setCoordMapper(cm);
}

/**
* Intersect with the Primitive, but apply the total transformation to the ray.
*/
Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {
    /*
    * Calculating the transformed ray.
    */
    Ray ray_trans(transformation_inv * ray.o, transformation_inv * ray.d);

    /*
    * Intersect transformed ray and return intersection with correct normal and original ray.
    */
    Intersection base_intersection = content_->intersect(ray_trans, previousBestDistance);

    if (!base_intersection) return Intersection::failure();
    
    Vector normal = (transformation_inv.transpose() * base_intersection.normal()).normalize();

    return Intersection(base_intersection.distance, ray, base_intersection.solid, normal, base_intersection.local());
}

/**
* Calculate the BBox of the primitive.
*/
BBox Instance::getBounds() const {
    BBox box = content_->getBounds();
    std::vector<Point> points;
    points.push_back(box.min);
    points.push_back(box.max);
    points.push_back(Point(box.min.x, box.min.y, box.max.z));
    points.push_back(Point(box.min.x, box.max.y, box.min.z));
    points.push_back(Point(box.max.x, box.min.y, box.min.z));
    points.push_back(Point(box.max.x, box.max.y, box.min.z));
    points.push_back(Point(box.max.x, box.min.y, box.max.z));
    points.push_back(Point(box.min.x, box.max.y, box.max.z));

    BBox temp = BBox::empty();
    for (Point& p : points) {
        temp.extend(transformation * p);
    }
    return temp;
}

}