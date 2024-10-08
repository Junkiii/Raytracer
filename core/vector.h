#ifndef CG1RAYTRACER_VECTOR_HEADER
#define CG1RAYTRACER_VECTOR_HEADER

#include <core/macros.h>
#include <core/point.h>
#include <core/float4.h>
#include <core/assert.h>
#include <algorithm>
#include <core/scalar.h>

namespace rt {

class Float4;
class Point;

/*
* Represents a 3-dimensional vector.
*/
class ALIGN(16) Vector {
public:
    float x, y, z;

    Vector() = default;
    Vector(float x, float y, float z);
    explicit Vector(const Float4& f4);

    static Vector rep(float v) { return Vector(v,v,v); }

    Vector operator + (const Vector& b) const;
    Vector operator - (const Vector& b) const;

    Vector operator - () const;

    Vector normalize() const;

    float lensqr() const;
    float length() const;

    bool operator == (const Vector& b) const;
    bool operator != (const Vector& b) const;

    //self defined:
    Vector operator / (const Vector& b) const;
    int maxComp() const;
    int minComp() const;
    int minCompAbs() const;
    float& operator[] (int index);
    float operator[] (int index) const;
};

Vector operator * (float scalar, const Vector& b);
Vector operator * (const Vector& a, float scalar);
Vector operator / (const Vector& a, float scalar);
Vector cross(const Vector& a, const Vector& b);
float dot(const Vector& a, const Vector& b);

Vector min(const Vector& a, const Vector& b);
Vector max(const Vector& a, const Vector& b);

Point operator + (const Point& a, const Vector& b);
Point operator + (const Vector& a, const Point& b);
Point operator - (const Point& a, const Vector& b);
Point operator * (const Float4& scale, const Point& p);
}

#endif