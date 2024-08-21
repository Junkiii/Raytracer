#include <rt/coordmappers/spherical.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
    : origin(origin), zenith(zenith), azimuthRef(azimuthRef)
{
    // If the zenith is not perpendicular to the azimuth:
    // Convert
    if (!fequal(dot(zenith, azimuthRef), .0f)) {
        this->azimuthRef = cross(cross(zenith, azimuthRef), zenith);
    }

    // Translating the sphere to the origin.
    Matrix transl = Matrix::identity();
    transl.r1.w = -origin.x;
    transl.r2.w = -origin.y;
    transl.r3.w = -origin.z;

    // Basis change
    // normalize for orthonormal basis
    Matrix B_prime = Matrix::system(azimuthRef.normalize(), -cross(zenith.normalize(), azimuthRef.normalize()), zenith.normalize());
    Matrix B = Matrix::system(Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1));
    transform = product(product(B_prime.invert(), B), transl);
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    Point transformed = transform * hit.local();
    
    float theta = atan2(sqrt(transformed.x * transformed.x + transformed.y * transformed.y), transformed.z);
    float phi = atan2(transformed.y, transformed.x);
    return Point(phi / pi * 0.5  * (1.0f / azimuthRef.length()), theta / pi * (1.0f / zenith.length()), .0f);

}

}