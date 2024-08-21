#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) 
    : e1(e1), e2(e2)
{
    // Basis change
    Matrix B_prime = Matrix::system(e1, e2, cross(e1,e2));
    Matrix B = Matrix::system(Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1));
    transform = product(B_prime.invert(), B);
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    return transform * hit.local();
}

}