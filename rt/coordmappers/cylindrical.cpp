#include <rt/coordmappers/cylindrical.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
    : origin(origin), longitudinalAxis(longitudinalAxis)
{
    this->polarAxis = polarAxis;
    // If the polar axis is not perpendicular to the longitudinal axis:
    // Convert the polar axis
    if (!fequal(dot(polarAxis, longitudinalAxis), .0f)) {
        this->polarAxis = cross(cross(longitudinalAxis, polarAxis), longitudinalAxis);
    }

    // Translating the cylinder to the origin.
    Matrix transl = Matrix::identity();
    transl.r1.w = -origin.x;
    transl.r2.w = -origin.y;
    transl.r3.w = -origin.z;

    // Basis change
    // normalize for orthonormal basis
    Matrix B_prime = Matrix::system(polarAxis.normalize(), -cross(longitudinalAxis.normalize(), polarAxis.normalize()), longitudinalAxis.normalize());
    Matrix B = Matrix::system(Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1));
    transform = product(product(B_prime.invert(), B), transl);
}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    // theta not used in formula on slides
    //float theta = atan2(sqrt(hit.hitPoint().x * hit.hitPoint().x + hit.hitPoint().y * hit.hitPoint().y), hit.hitPoint().z);
    
    Point transformed = transform * hit.local();

    float phi = atan2(transformed.y, transformed.x);
    return Point(phi / pi * 0.5 * (1.0f / polarAxis.length()), transformed.z / longitudinalAxis.length(), .0f);
}

}