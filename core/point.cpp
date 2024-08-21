#include <core/point.h>

namespace rt {

Point::Point(float x, float y, float z)
    : x(x), y(y), z(z) {}

/**
* Creates a Point from a Float4. 
* Calculates homogenous coordinates.
* (-DIFF-)
*/
Point::Point(const Float4& f4)
    : x(fdiv(f4.x, f4.w)), y(fdiv(f4.y, f4.w)), z(fdiv(f4.z, f4.w)) {}

Vector Point::operator - (const Point& b) const {
    return Vector(x - b.x, y - b.y, z - b.z);
}

/**
* Checking for equality component wise.
* Is using epsilon! (Uses fequal(float a, float b) in scalar.h)
*/
bool Point::operator == (const Point& b) const {
    return (fequal(x, b.x) && fequal(y, b.y) && fequal(z, b.z));
}

/**
* Checking for unequality component wise.
* Is using epsilon! (Uses fequal(float a, float b) in scalar.h)
*/
bool Point::operator != (const Point& b) const {
    return !(*this == b);
}

Point operator * (float scalar, const Point& b) {
    return Point(b.x * scalar, b.y * scalar, b.z * scalar);
}

Point operator * (const Point& a, float scalar) {
    return Point(a.x * scalar, a.y * scalar, a.z * scalar);
}

Point operator+(const Point& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

/**
* Computes component-wise minimum.
*/
Point min(const Point& a, const Point& b) {
    return Point(fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z));
}

/**
* Computes component-wise maximum.
*/
Point max(const Point& a, const Point& b) {
    return Point(fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z));
}

float& Point::operator[] (int index) {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    float err = -1;
    return err;
}

float Point::operator[] (int index) const {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    float err = -1;
    return err;
}

}
