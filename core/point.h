#ifndef CG1RAYTRACER_POINT_HEADER
#define CG1RAYTRACER_POINT_HEADER

#include <core/assert.h>
#include <core/float4.h>
#include <core/scalar.h>
#include <core/vector.h>
#include <core/macros.h>

namespace rt {

class Vector;
class Float4;

/*
* Represents a 3-dimensional point.
*/
class ALIGN(16) Point {
public:
    float x, y, z;

    Point() = default;
    Point(float x, float y, float z);
    explicit Point(const Float4& f4);

    static Point rep(float v) { return Point(v,v,v); }

    Vector operator-(const Point& b) const;

    bool operator==(const Point& b) const;
    bool operator!=(const Point& b) const;

    //self defined:
    float& operator[] (int index);
    float operator[] (int index) const;
};

Point operator*(float scalar, const Point& b);
Point operator*(const Point& a, float scalar);
Point operator+(const Point& a, const Point& b);

Point min(const Point& a, const Point& b);
Point max(const Point& a, const Point& b);
}

#endif